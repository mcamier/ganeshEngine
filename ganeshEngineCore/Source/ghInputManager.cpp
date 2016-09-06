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
	mInputConfig.dump();
	vector<InputContext *> &ictxs = mInputConfig.getInputContexts();
	for (int i = 0; i < ictxs.size(); i++) {
		InputContext *ptr = ictxs[i];
		int id = ptr->getId();
		mInputContexts.insert(pair<stringId, unique_ptr<InputContext>>(id, unique_ptr<InputContext>(ptr)));
		activeContext(id, true);
	}

    for (int i = 0 ; i <= GH_MAX_JOYSTICK ; i++) {
        mJoysticks[i].initialize(i);
    }

	gEvent().addListener<InputManager>(GH_EVENT_JOYSTICK_STATE_CHANGE, this, &InputManager::onJoystickStateChange);
	_DEBUG("InputManager initialized", LOG_CHANNEL::INPUT);
}

void InputManager::vDestroy() {
	_DEBUG("InputManager destroyed", LOG_CHANNEL::INPUT);
}

void InputManager::activeContext(stringId id, bool active) {
	auto iter = mInputContexts.find(id);
	if (iter != mInputContexts.end()) {
		_DEBUG("InputContext with id : " << id << " activated", LOG_CHANNEL::INPUT);
		iter->second->setActive(active);
	} else {
		_ERROR("Cannot active the inputContext with id : " << id, LOG_CHANNEL::INPUT);
	}
}

void InputManager::registerInputContext(unique_ptr<InputContext> inputContext) {
	auto iter = mInputContexts.find(inputContext->getId());
	if (iter != mInputContexts.end()) {
		_ERROR("Cannot add an inputContext already present in the InputManager", LOG_CHANNEL::INPUT);
	}
	mInputContexts.insert(make_pair(inputContext->getId(), move(inputContext)));
}

void InputManager::registerInputCallback(stringId callbackHash, InputCallbackType callback) {
	mInputCallbacks.insert(make_pair(callbackHash, callback));
}

void InputManager::registerInput(RawInput rawInput) {
	mFrameRawInputs.push(rawInput);
	_DEBUG(
		"RawInput registered : [" << inputDetails::toString(rawInput.source) << ", "
								  << inputDetails::toString(rawInput.type)
								  << ", " << inputDetails::toString(rawInput.code), LOG_CHANNEL::INPUT);
}

void InputManager::vUpdate(const Clock &clock) {
	float secondElapsedSinceLastFrame = clock.getLastFrameElapsedTimeAsSecond();

	glfwPollEvents();

	for(Joystick& device : mJoysticks) {
		device.update();
	}

	/* loop over list of held button and submit input accordingly */
	for(auto itr : mHeldButtonRawInputs) {
		registerInput(itr.second);
	}

	bool inputFoundInChord = false;
	while (!mFrameRawInputs.empty()) {
		auto input = mFrameRawInputs.front();
		inputFoundInChord = false;

		/* check if input exist in any chord in any active context
		 */
		for (auto const &entry : mInputContexts) {
			InputContext &context = (*entry.second);
			if (context.isActive()) {
				for (auto const &chord : context.m_chords) {
					/* Chord inputs are now limited to input of type BUTTON_PRESS only
					 */
					if (input.type == InputType::BUTTON_PRESS &&
						chord.containsRawInput(input.source, input.type, input.code)) {
						inputFoundInChord = true;
					}
				}
			}
		}
		if (inputFoundInChord) {
			/* if input could potentially triggers a chord, it is postponed in another container and
			 * removed from the input queue
			 */
			mPostponedRawInputs.push_back(input);
			//_DEBUG("INPUT POSTPONED : " << inputDetails::toString(input.source) << ", " << inputDetails::toString(input.type), LOG_CHANNEL::INPUT);
		} else {
			/** trigger regular action for this input */
			triggerPlainInputAction(input, secondElapsedSinceLastFrame);
		}
		mFrameRawInputs.pop();
	}

	/* Update and detects chords
	 * btw it's quite ugly
	 */
	for (auto const &entry : mInputContexts) {
		InputContext &context = (*entry.second);
		if (context.isActive() && !mPostponedRawInputs.empty()) {
			for (auto const &chord : context.m_chords) {
				if (chord.size == InputChordSize::_2) {
					int a = chord.findFirstInputFrom(mPostponedRawInputs);
					int b = chord.findSecondInputFrom(mPostponedRawInputs);
					if (a >= 0 && b >= 0) {
						_DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
						if (a > b) {
							mPostponedRawInputs.erase(mPostponedRawInputs.begin() + a);
							mPostponedRawInputs.erase(mPostponedRawInputs.begin() + b);
						} else {
							mPostponedRawInputs.erase(mPostponedRawInputs.begin() + b);
							mPostponedRawInputs.erase(mPostponedRawInputs.begin() + a);
						}

						auto iter = mInputCallbacks.find(chord.m_callbackNameHash);
						if (iter != mInputCallbacks.end()) {
							iter->second(RawInput(), secondElapsedSinceLastFrame);
						} else {
							_WARNING("Input chord detected but no callback to call", LOG_CHANNEL::INPUT);
						}

					}
				} else if (chord.size == InputChordSize::_3) {
					int a = chord.findFirstInputFrom(mPostponedRawInputs);
					int b = chord.findSecondInputFrom(mPostponedRawInputs);
					int c = chord.findThirdInputFrom(mPostponedRawInputs);
					if (a >= 0 && b >= 0 && c >= 0) {
						_DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
						mPostponedRawInputs.erase(mPostponedRawInputs.begin() + a);
						mPostponedRawInputs.erase(mPostponedRawInputs.begin() + b);
						mPostponedRawInputs.erase(mPostponedRawInputs.begin() + c);
						vector<int> pouet = vector<int>(3);
						pouet.push_back(a);
						pouet.push_back(b);
						pouet.push_back(c);
						std::sort(pouet.begin(), pouet.end());
						for (auto itr = pouet.rbegin(); itr != pouet.rend(); ++itr) {
							int t = (*itr);
							mPostponedRawInputs.erase(mPostponedRawInputs.begin() + t);
						}

						auto iter = mInputCallbacks.find(chord.m_callbackNameHash);
						if (iter != mInputCallbacks.end()) {
							iter->second(RawInput(), secondElapsedSinceLastFrame);
						} else {
							_WARNING("Input chord detected but no callback to call", LOG_CHANNEL::INPUT);
						}
					}
				}
			}
		}
	}

	/* apply lifetime on remaining input and remove the too old ones
	 */
	for (auto itr = mPostponedRawInputs.begin(); itr != mPostponedRawInputs.end();) {
		(*itr).chordDetectionLifetimeS -= secondElapsedSinceLastFrame;
		if ((*itr).chordDetectionLifetimeS <= 0) {
			triggerPlainInputAction((*itr), secondElapsedSinceLastFrame);
			mPostponedRawInputs.erase(itr);
		} else {
			++itr;
		}
	}
}

void InputManager::triggerPlainInputAction(RawInput ri, float deltaTime) {
	for (auto const &entry : mInputContexts) {
		InputContext &context = (*entry.second);
		if (context.isActive()) {
			stringId callbackId;
			if (context.getInputMatch(ri, &callbackId)) {
				auto iter = mInputCallbacks.find(callbackId);
				if (iter != mInputCallbacks.end()) {
					_DEBUG("INPUT MATCH TRIGERRED BY " << inputDetails::toString(ri.source) << ", "
													   << inputDetails::toString(ri.type) << ", "
													   << inputDetails::toString(ri.code), LOG_CHANNEL::INPUT);
					iter->second(ri, deltaTime);
				} else {
					_WARNING("Input detected but no callback to call", LOG_CHANNEL::INPUT);
				}
			}

			if(ri.type == InputType::BUTTON_PRESS) {
				auto itr = mHeldButtonRawInputs.find(ri.code);

				if(itr == mHeldButtonRawInputs.end()) {
					ri.type = InputType::BUTTON_DOWN;
					mHeldButtonRawInputs.insert(make_pair(ri.code, ri));
				}
			} else if(ri.type == InputType::BUTTON_RELEASE) {
				auto itr = mHeldButtonRawInputs.find(ri.code);

				if(itr != mHeldButtonRawInputs.end()) {
					mHeldButtonRawInputs.erase(itr);
				}
			}
		}
	}
}

void InputManager::onJoystickStateChange(Event *event) {
	JoystickStateChangeEvent *jsce = static_cast<JoystickStateChangeEvent *>(event);
	int i = jsce->getJoystickIndex();
	if (i >= 0 || i <= GH_MAX_JOYSTICK) {
		if (jsce->getJoystickState() == GLFW_CONNECTED) {
			mJoysticks[i].initialize(i);
			_DEBUG("Joystick [" << i << "] connected", LOG_CHANNEL::INPUT);
		} else if (jsce->getJoystickState() == GLFW_DISCONNECTED) {
			mJoysticks[i].release();
			_DEBUG("Joystick [" << i << "] disconnected", LOG_CHANNEL::INPUT);
		}
	} else {
		_DEBUG("onJoystickStateChange with invalid index [" << i << "]", LOG_CHANNEL::INPUT);
	}
}

void InputManager::initCallbacks() {
	glfwSetWindowUserPointer(gPlatform().getWindow(), this);
	glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
		if (action != GLFW_REPEAT) {
			InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
			RawInput input;
			input.idx = 0;
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
		input.source = InputSource::MOUSE;
		input.type = InputType::AXIS;
		input.data.axis.x = (F32)xpos;
		input.data.axis.y = (F32)ypos;
		input.data.axis.z = 0.0f;

		mgr->registerInput(input);
	});

	glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
		if (action != GLFW_REPEAT) {
			InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
			RawInput input;
			input.idx = 0;
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
		input.source = InputSource::MOUSE;
		input.type = InputType::AXIS;
		input.data.axis.x = (F32)offsetX;
		input.data.axis.y = (F32)offsetY;
		input.data.axis.z = 0.0f;

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

