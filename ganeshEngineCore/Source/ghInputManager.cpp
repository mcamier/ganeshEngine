#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <algorithm>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

void InputManager::vInitialize() {
	for (int i = 0; i < GH_KEYBOARD_KEY_COUNT; i++) {
		m_keyboardButtonsState[i].idx = 0;
		m_keyboardButtonsState[i].source = RawInput::SOURCE::KEYBOARD;
		m_keyboardButtonsState[i].type = RawInput::TYPE::RELEASE;
		m_keyboardButtonsState[i].key = (RawInput::KEY)ghKeyboardKeys[i];
	}

	for (int i = 0; i < GH_MOUSE_KEY_COUNT; i++) {
		m_mouseButtonsState[i].idx = 0;
		m_mouseButtonsState[i].source = RawInput::SOURCE::MOUSE;
		m_mouseButtonsState[i].type = RawInput::TYPE::RELEASE;
		m_mouseButtonsState[i].key = (RawInput::KEY)ghMouseKeys[i];
	}

	glfwSetWindowUserPointer(gPlatform().getWindow(), this);
	glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.chordDetectionLifetimeS = Chord::DETECTION_DURATION_SECOND;
		input.source = RawInput::SOURCE::KEYBOARD;
		input.key = (RawInput::KEY)key;
		input.data.button.mods = mods;

		switch (action) {
			case GLFW_PRESS: {
				input.type = RawInput::TYPE::PRESS;
				mgr->setKeyboardState(key, RawInput::TYPE::PRESS);
				mgr->m_frameRawInputs.push(input);
				break;
			}
			case GLFW_RELEASE: {
				input.type = RawInput::TYPE::RELEASE;
				mgr->setKeyboardState(key, RawInput::TYPE::RELEASE);
				mgr->m_frameRawInputs.push(input);
				break;
			}
		}
	});

	glfwSetCursorPosCallback(gPlatform().getWindow(), [](GLFWwindow *window, double xpos, double ypos) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.chordDetectionLifetimeS = Chord::DETECTION_DURATION_SECOND;
		input.source = RawInput::SOURCE::MOUSE;
		input.type = RawInput::TYPE::MOVE;
		input.data.move.x = xpos;
		input.data.move.y = ypos;

		mgr->m_frameRawInputs.push(input);
	});

	glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.chordDetectionLifetimeS = Chord::DETECTION_DURATION_SECOND;
		input.source = RawInput::SOURCE::MOUSE;
		input.key = (RawInput::KEY)button;
		input.data.button.mods = mods;

		switch (action) {
			case GLFW_PRESS:
				input.type = RawInput::TYPE::PRESS;
				mgr->setMouseState(button, RawInput::TYPE::PRESS);
				mgr->m_frameRawInputs.push(input);
				//_DEBUG("rawInput registered : [" << RawInput::toString(input.source) << "] [" << RawInput::toString(input.type) << "]", LOG_CHANNEL::INPUT);
				break;
			case GLFW_RELEASE:
				input.type = RawInput::TYPE::RELEASE;
				mgr->setMouseState(button, RawInput::TYPE::RELEASE);
				mgr->m_frameRawInputs.push(input);
				//_DEBUG("rawInput registered : [" << RawInput::toString(input.source) << "] [" << RawInput::toString(input.type) << "]", LOG_CHANNEL::INPUT);
				break;
		}
	});

	glfwSetScrollCallback(gPlatform().getWindow(), [](GLFWwindow *window, double offsetX, double offsetY) {
		InputManager *mgr = static_cast<InputManager *>(glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.chordDetectionLifetimeS = Chord::DETECTION_DURATION_SECOND;
		input.source = RawInput::SOURCE::MOUSE;
		input.type = RawInput::TYPE::RANGE;
		input.data.range.x = offsetX;
		input.data.range.y = offsetY;
		input.data.range.z = 0;
		mgr->m_frameRawInputs.push(input);
		//_DEBUG("rawInput registered : [" << RawInput::toString(input.source) << "] [" << RawInput::toString(input.type) << "]", LOG_CHANNEL::INPUT);
	});

	/** Add default input detection to exit the game when ESC is pressed */
	unique_ptr<InputContext> inputContext = make_unique<InputContext>(GH_HASH("__GH_INPUT_CONTEXT_SYSTEM"));
	int id = inputContext->getId();
	InputMatch *inputMatch = new InputMatch(
			RawInput::SOURCE::KEYBOARD,
			RawInput::TYPE::PRESS,
			RawInput::KEY::ESCAPE,
			GH_HASH("__GH_INPUT_EXIT_GAME"));
	inputContext->registerMatch(*inputMatch);

	this->registerInputCallback(GH_HASH("__GH_INPUT_EXIT_GAME"), [](rawInput ri, float deltaTime) {
		gApp().shutdown();
	});

	this->registerInputContext(move(inputContext));
	this->activeContext(id, true);

	/** Read and configuration from conf object */
    _DEBUG("############################", LOG_CHANNEL::INPUT);
    m_config.dump();
    vector<InputContext*> &ictxs = m_config.getInputContexts();
    for (int i = 0; i < ictxs.size(); i++) {
        InputContext* ptr = ictxs[i];
        int id = ptr->getId();
        m_inputContexts.insert(pair<int, unique_ptr<InputContext>>(id, unique_ptr<InputContext>(ptr)));
        activeContext(id, true);
    }

	gEvent().addListener<InputManager>(GH_HASH("__GH_EVENT_JOYSTICK_STATE_CHANGE"), this, &InputManager::onJoystickStateChange);

	for (int i = 0; i <= GH_MAX_JOYSTICK; i++) {
		if (GLFW_TRUE == glfwJoystickPresent(i)) {
			m_joystick[i] = new Joystick(i);
		}else {
			m_joystick[i] = nullptr;
		}
	}

	_DEBUG("InputManager initialized", LOG_CHANNEL::INPUT);
}

void InputManager::vDestroy() {
	for (int i = 0; i <= GH_MAX_JOYSTICK; i++) {
		if (m_joystick[i] != nullptr) {
			delete(m_joystick[i]);
		}
	}
	_DEBUG("InputManager destroyed", LOG_CHANNEL::INPUT);
}

void InputManager::activeContext(int id, bool active) {
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

void InputManager::registerInputCallback(U32 callbackHash, InputCallbackType callback) {
	m_inputCallbacks.insert(make_pair(callbackHash, callback));
}

void InputManager::update(float deltaTime) {
	/** Detection of held key, I dont rely on GLFW action repeat because of the
	 * delay between press and the firist triggered hold input */
	updateStates(m_keyboardButtonsState, GH_KEYBOARD_KEY_COUNT);
	updateStates(m_mouseButtonsState, GH_MOUSE_KEY_COUNT);

	glfwPollEvents();
	for (int i = 0; i <= GH_MAX_JOYSTICK; i++) {
		if (m_joystick[i] != nullptr) {
			m_joystick[i]->update();
		}
	}

    bool inputFoundInChord = false;
    while(!m_frameRawInputs.empty()) {
        auto input = m_frameRawInputs.front();
        inputFoundInChord = false;

        /** check if input exist in any chord in any active context */
        for (auto const &entry : m_inputContexts) {
            InputContext &context = (*entry.second);
            if (context.isActive()) {
                for (auto const &chord : context.m_chords) {
                    if (chord.containsRawInput(input.source, input.type, input.key)) {
                        inputFoundInChord=true;
                    }
                }
            }
        }
        if(inputFoundInChord){
            /** if input could potentially triggers a chord, it is postponed in another container and
             * removed from the input queue */
            m_postponedRawInputs.push_back(input);
            //_DEBUG("INPUT POSTPONED : " << RawInput::toString(input.source) << ", " << RawInput::toString(input.type), LOG_CHANNEL::INPUT);
        }else {
            /** trigger regular action for this input */
			triggerPlainInputAction(input, deltaTime);
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
                if (chord.size == CHORD_SIZE::_2) {
                    int a = chord.findFirstInputFrom(m_postponedRawInputs);
                    int b = chord.findSecondInputFrom(m_postponedRawInputs);
                    if(a>=0 && b>=0) {
                        _DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
                        if(a>b) {
                            m_postponedRawInputs.erase(m_postponedRawInputs.begin()+a);
                            m_postponedRawInputs.erase(m_postponedRawInputs.begin()+b);
                        }else{
                            m_postponedRawInputs.erase(m_postponedRawInputs.begin()+b);
                            m_postponedRawInputs.erase(m_postponedRawInputs.begin()+a);
                        }

						auto iter = m_inputCallbacks.find(chord.m_callbackNameHash);
						if (iter != m_inputCallbacks.end()) {
							iter->second(rawInput(), deltaTime);
						} else {
							_WARNING("Input chord detected but no callback to call", LOG_CHANNEL::INPUT);
						}

                    }
                } else if (chord.size == CHORD_SIZE::_3) {
                    int a = chord.findFirstInputFrom(m_postponedRawInputs);
                    int b = chord.findSecondInputFrom(m_postponedRawInputs);
                    int c = chord.findThirdInputFrom(m_postponedRawInputs);
                    if(a>=0 && b>=0 && c>=0){
                        _DEBUG("CHORD DETECTED", LOG_CHANNEL::INPUT);
                        m_postponedRawInputs.erase(m_postponedRawInputs.begin()+a);
                        m_postponedRawInputs.erase(m_postponedRawInputs.begin()+b);
                        m_postponedRawInputs.erase(m_postponedRawInputs.begin()+c);
                        vector<int> pouet = vector<int>(3);
                        pouet.push_back(a);pouet.push_back(b);pouet.push_back(c);
                        std::sort(pouet.begin(), pouet.end());
                        for(auto itr = pouet.rbegin() ; itr!= pouet.rend() ; ++itr) {
                            int t = (*itr);
                            m_postponedRawInputs.erase(m_postponedRawInputs.begin()+t);
                        }

						auto iter = m_inputCallbacks.find(chord.m_callbackNameHash);
						if (iter != m_inputCallbacks.end()) {
							iter->second(rawInput(), deltaTime);
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
    for(auto itr = m_postponedRawInputs.begin() ; itr!= m_postponedRawInputs.end() ; ) {
        (*itr).chordDetectionLifetimeS -= deltaTime;
        if((*itr).chordDetectionLifetimeS <= 0){
			triggerPlainInputAction((*itr), deltaTime);
			m_postponedRawInputs.erase(itr);
            //_DEBUG("INPUT FOR CHORD DETECTION LIFETIME OVER", LOG_CHANNEL::INPUT);
        }else{
            ++itr;
        }
    }
}

void InputManager::triggerPlainInputAction(rawInput ri, float deltaTime) {
	for (auto const &entry : m_inputContexts) {
		InputContext &context = (*entry.second);
		if (context.isActive()) {
			U32 callbackId;
			if (context.getInputMatch(ri, &callbackId)) {
				auto iter = m_inputCallbacks.find(callbackId);
				if (iter != m_inputCallbacks.end()) {
					_DEBUG("INPUT MATCH TRIGERRED BY " << RawInput::toString(ri.source) << ", " << RawInput::toString(ri.type) << ", " << RawInput::toString(ri.key), LOG_CHANNEL::INPUT);
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
	if (jsce->getJoystickIndex() < 0 || jsce->getJoystickIndex() > GH_MAX_JOYSTICK) {
		_DEBUG("onJoystickStateChange with invalid index [" << jsce->getJoystickIndex() << "]", LOG_CHANNEL::INPUT);
	} else {
		if (jsce->getJoystickState() == GLFW_CONNECTED) {
			_DEBUG("Joystick [" << jsce->getJoystickIndex() << "] connected", LOG_CHANNEL::INPUT);
			m_joystick[jsce->getJoystickIndex()] = new Joystick(jsce->getJoystickIndex());
		} else if (jsce->getJoystickState() == GLFW_DISCONNECTED) {
			_DEBUG("Joystick [" << jsce->getJoystickIndex() << "] disconnected", LOG_CHANNEL::INPUT);
			delete(m_joystick[jsce->getJoystickIndex()]);
			m_joystick[jsce->getJoystickIndex()] = nullptr;
		}
	}
}

void InputManager::setKeyboardState(int key, RawInput::TYPE type) {
	if (type == RawInput::TYPE::PRESS ||
		type == RawInput::TYPE::RELEASE ||
		type == RawInput::TYPE::DOWN) {
		m_keyboardButtonsState[key].type = type;
	}
}

void InputManager::setMouseState(int button, RawInput::TYPE type) {
	if (type == RawInput::TYPE::PRESS ||
		type == RawInput::TYPE::RELEASE ||
		type == RawInput::TYPE::DOWN) {
		m_mouseButtonsState[button].type = type;
	}
}

void InputManager::updateStates(rawInput target[], int size) {
	for (int i = 0; i < size; i++) {
		if (target[i].type == RawInput::TYPE::PRESS) {
            target[i].type = RawInput::TYPE::DOWN;
            m_frameRawInputs.push(target[i]);
		} else if (target[i].type == RawInput::TYPE::DOWN) {
            m_frameRawInputs.push(target[i]);
		}
	}
}

InputManager &(*gInput)() = &InputManager::get;
}

