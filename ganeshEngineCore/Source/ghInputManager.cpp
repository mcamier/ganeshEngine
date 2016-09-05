#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <algorithm>

namespace ganeshEngine {

static stringId GH_INPUT_CONTEXT_SYSTEM = gInternString("__GH_INPUT_CONTEXT_SYSTEM");
static stringId GH_INPUT_EXIT_GAME = gInternString("__GH_INPUT_EXIT_GAME");

void InputManager::vInitialize() {
	initCallbacks();
	initDefaultInputContext();

	/** Read and configuration from conf object */
	_DEBUG("############################", LOG_CHANNEL::INPUT);
	m_config.dump();
	vector<InputContext *> &ictxs = m_config.getInputContexts();
	for (int i = 0; i < ictxs.size(); i++) {
		InputContext *ptr = ictxs[i];
		int id = ptr->getId();
		m_inputContexts.insert(pair<stringId, unique_ptr<InputContext>>(id, unique_ptr<InputContext>(ptr)));
		activeContext(id, true);
	}

	gEvent().addListener<InputManager>(GH_EVENT_JOYSTICK_STATE_CHANGE, this, &InputManager::onJoystickStateChange);
	_DEBUG("InputManager initialized", LOG_CHANNEL::INPUT);
}

void InputManager::vDestroy() {
	_DEBUG("InputManager destroyed", LOG_CHANNEL::INPUT);
}

void InputManager::activeContext(stringId id, bool active) {
	auto iter = m_inputContexts.find(id);
	if (iter != m_inputContexts.end()) {
		_DEBUG("InputContext with id : " << id << " activated", LOG_CHANNEL::INPUT);
		iter->second->setActive(active);
	} else {
		_ERROR("Cannot active the inputContext with id : " << id, LOG_CHANNEL::INPUT);
	}
}

void InputManager::registerInputContext(unique_ptr<InputContext> inputContext) {
	auto iter = m_inputContexts.find(inputContext->getId());
	if (iter != m_inputContexts.end()) {
		_ERROR("Cannot add an inputContext already present in the InputManager", LOG_CHANNEL::INPUT);
	}
	m_inputContexts.insert(make_pair(inputContext->getId(), move(inputContext)));
}

void InputManager::registerInputCallback(stringId callbackHash, InputCallbackType callback) {
	m_inputCallbacks.insert(make_pair(callbackHash, callback));
}

void InputManager::registerInput(RawInput rawInput) {
	m_frameRawInputs.push(rawInput);
	_DEBUG(
		"RawInput registered : [" << inputDetails::toString(rawInput.source) << ", "
								  << inputDetails::toString(rawInput.type)
								  << ", " << inputDetails::toString(rawInput.code), LOG_CHANNEL::INPUT);
}

void InputManager::vUpdate(const Clock &clock) {
	float secondElapsedSinceLastFrame = clock.getLastFrameElapsedTimeAsSecond();

	glfwPollEvents();

	bool inputFoundInChord = false;
	while (!m_frameRawInputs.empty()) {
		auto input = m_frameRawInputs.front();
		inputFoundInChord = false;

		/** check if input exist in any chord in any active context */
		for (auto const &entry : m_inputContexts) {
			InputContext &context = (*entry.second);
			if (context.isActive()) {
				for (auto const &chord : context.m_chords) {
					if (chord.containsRawInput(input.source, input.type, input.code)) {
						inputFoundInChord = true;
					}
				}
			}
		}
		if (inputFoundInChord) {
			/** if input could potentially triggers a chord, it is postponed in another container and
			 * removed from the input queue */
			m_postponedRawInputs.push_back(input);
			//_DEBUG("INPUT POSTPONED : " << inputDetails::toString(input.source) << ", " << inputDetails::toString(input.type), LOG_CHANNEL::INPUT);
		} else {
			/** trigger regular action for this input */
			triggerPlainInputAction(input, secondElapsedSinceLastFrame);
		}
		m_frameRawInputs.pop();
	}

	/**
	 * Update and detects chords
	 * btw it's quite ugly
	 */
	for (auto const &entry : m_inputContexts) {
		InputContext &context = (*entry.second);
		if (context.isActive() && !m_postponedRawInputs.empty()) {
			for (auto const &chord : context.m_chords) {
				if (chord.size == InputChordSize::_2) {
					int a = chord.findFirstInputFrom(m_postponedRawInputs);
					int b = chord.findSecondInputFrom(m_postponedRawInputs);
					if (a >= 0 && b >= 0) {
						_DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
						if (a > b) {
							m_postponedRawInputs.erase(m_postponedRawInputs.begin() + a);
							m_postponedRawInputs.erase(m_postponedRawInputs.begin() + b);
						} else {
							m_postponedRawInputs.erase(m_postponedRawInputs.begin() + b);
							m_postponedRawInputs.erase(m_postponedRawInputs.begin() + a);
						}

						auto iter = m_inputCallbacks.find(chord.m_callbackNameHash);
						if (iter != m_inputCallbacks.end()) {
							iter->second(RawInput(), secondElapsedSinceLastFrame);
						} else {
							_WARNING("Input chord detected but no callback to call", LOG_CHANNEL::INPUT);
						}

					}
				} else if (chord.size == InputChordSize::_3) {
					int a = chord.findFirstInputFrom(m_postponedRawInputs);
					int b = chord.findSecondInputFrom(m_postponedRawInputs);
					int c = chord.findThirdInputFrom(m_postponedRawInputs);
					if (a >= 0 && b >= 0 && c >= 0) {
						_DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
						m_postponedRawInputs.erase(m_postponedRawInputs.begin() + a);
						m_postponedRawInputs.erase(m_postponedRawInputs.begin() + b);
						m_postponedRawInputs.erase(m_postponedRawInputs.begin() + c);
						vector<int> pouet = vector<int>(3);
						pouet.push_back(a);
						pouet.push_back(b);
						pouet.push_back(c);
						std::sort(pouet.begin(), pouet.end());
						for (auto itr = pouet.rbegin(); itr != pouet.rend(); ++itr) {
							int t = (*itr);
							m_postponedRawInputs.erase(m_postponedRawInputs.begin() + t);
						}

						auto iter = m_inputCallbacks.find(chord.m_callbackNameHash);
						if (iter != m_inputCallbacks.end()) {
							iter->second(RawInput(), secondElapsedSinceLastFrame);
						} else {
							_WARNING("Input chord detected but no callback to call", LOG_CHANNEL::INPUT);
						}
					}
				}
			}
		}
	}

	/**
	 * apply lifetime on remaining input and remove the too old ones
	 */
	for (auto itr = m_postponedRawInputs.begin(); itr != m_postponedRawInputs.end();) {
		(*itr).chordDetectionLifetimeS -= secondElapsedSinceLastFrame;
		if ((*itr).chordDetectionLifetimeS <= 0) {
			triggerPlainInputAction((*itr), secondElapsedSinceLastFrame);
			m_postponedRawInputs.erase(itr);
			//_DEBUG("INPUT FOR CHORD DETECTION LIFETIME OVER", LOG_CHANNEL::INPUT);
		} else {
			++itr;
		}
	}
}

void InputManager::triggerPlainInputAction(RawInput ri, float deltaTime) {
	for (auto const &entry : m_inputContexts) {
		InputContext &context = (*entry.second);
		if (context.isActive()) {
			stringId callbackId;
			if (context.getInputMatch(ri, &callbackId)) {
				auto iter = m_inputCallbacks.find(callbackId);
				if (iter != m_inputCallbacks.end()) {
					_DEBUG("INPUT MATCH TRIGERRED BY " << inputDetails::toString(ri.source) << ", "
													   << inputDetails::toString(ri.type) << ", "
													   << inputDetails::toString(ri.code), LOG_CHANNEL::INPUT);
					iter->second(ri, deltaTime);
				} else {
					_WARNING("Input detected but no callback to call", LOG_CHANNEL::INPUT);
				}
			}
		}
	}
}

void InputManager::onJoystickStateChange(Event *event) {
	JoystickStateChangeEvent *jsce = static_cast<JoystickStateChangeEvent *>(event);
	/*if (jsce->getJoystickIndex() < 0 || jsce->getJoystickIndex() > GH_MAX_JOYSTICK) {
		_DEBUG("onJoystickStateChange with invalid index [" << jsce->getJoystickIndex() << "]", LOG_CHANNEL::INPUT);
	} else {
		if (jsce->getJoystickState() == GLFW_CONNECTED) {
			_DEBUG("Joystick [" << jsce->getJoystickIndex() << "] connected", LOG_CHANNEL::INPUT);
			m_joystick[jsce->getJoystickIndex()] = new Joystick(jsce->getJoystickIndex());
		} else if (jsce->getJoystickState() == GLFW_DISCONNECTED) {
			_DEBUG("Joystick [" << jsce->getJoystickIndex() << "] disconnected", LOG_CHANNEL::INPUT);
			delete (m_joystick[jsce->getJoystickIndex()]);
			m_joystick[jsce->getJoystickIndex()] = nullptr;
		}
	}*/
}

void InputManager::initCallbacks() {
	glfwSetWindowUserPointer(gPlatform().getWindow(), this);
	glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
		if (action != GLFW_REPEAT) {
			InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
			RawInput input;
			input.idx = 0;
			input.timestamp = 0;
			input.source = InputSource::KEYBOARD;
			input.code = inputDetails::sysInputKeyboardCode2GHCode(key);
			if (action == GLFW_PRESS) input.type = InputType::BUTTON_PRESS;
			else if (action == GLFW_RELEASE) input.type = InputType::BUTTON_RELEASE;

			mgr->registerInput(input);
		}
	});

	glfwSetCursorPosCallback(gPlatform().getWindow(), [](GLFWwindow *window, double xpos, double ypos) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		RawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = InputSource::MOUSE;
		input.type = InputType::AXIS;
		input.data.range.x = xpos;
		input.data.range.y = ypos;
		input.data.range.z = 0.0f;

		mgr->registerInput(input);
	});

	glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
		if (action != GLFW_REPEAT) {
			InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
			RawInput input;
			input.idx = 0;
			input.timestamp = 0;
			input.source = InputSource::MOUSE;
			input.code = inputDetails::sysInputMouseCode2GHCode(button);
			if (action == GLFW_PRESS) input.type = InputType::BUTTON_PRESS;
			else if (action == GLFW_RELEASE) input.type = InputType::BUTTON_RELEASE;

			mgr->registerInput(input);
		}
	});

	glfwSetScrollCallback(gPlatform().getWindow(), [](GLFWwindow *window, double offsetX, double offsetY) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		RawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = InputSource::MOUSE;
		input.type = InputType::AXIS;
		input.data.range.x = offsetX;
		input.data.range.y = offsetY;
		input.data.range.z = 0;

		mgr->registerInput(input);
	});
}

void InputManager::initDefaultInputContext() {
	unique_ptr<InputContext> inputContext = make_unique<InputContext>(GH_INPUT_CONTEXT_SYSTEM);
	int id = inputContext->getId();
	InputMatch *inputMatch = new InputMatch(
		InputSource::KEYBOARD,
		InputType::BUTTON_PRESS,
		InputCode::KEYBOARD_ESCAPE,
		GH_INPUT_EXIT_GAME);
	inputContext->registerMatch(*inputMatch);

	this->registerInputCallback(GH_INPUT_EXIT_GAME, [](RawInput ri, float deltaTime) {
		gEvent().fireEvent(new Event(GH_EVENT_EXIT_GAME));
	});

	this->registerInputContext(move(inputContext));
	this->activeContext(id, true);
}

InputManager &(*gInput)() = &InputManager::get;
}

