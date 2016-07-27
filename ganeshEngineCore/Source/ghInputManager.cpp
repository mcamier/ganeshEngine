#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <GLFW/glfw3.h>

namespace ganeshEngine {

void InputManager::vInitialize()
{
    for (int i = 0; i < GH_BUTTON_ARRAY_SIZE; i++) {
		m_keyState[i] = GH_STATE_RELEASED;
    }

    glfwSetWindowUserPointer(gPlatform().getWindow(), this);
    glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods)
    {
		InputManager *mgr = static_cast<InputManager*> (glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = RawInput::SOURCE::KEYBOARD;
		input.data.button.key = key;
		input.data.button.scancode = scancde;
		input.data.button.mods = mods;

		switch (action) {
		case GLFW_PRESS:
		{
			input.type = RawInput::TYPE::PRESS;
				mgr->m_keyState[key] = GH_STATE_PRESSED;
				mgr->rawInputs.push_back(input);
				_DEBUG("rawInput registered : [KEYBOARD] [" << RawInput::toString(input.type) << "]", LOG_CHANNEL::INPUT);
			break;
		}
		case GLFW_RELEASE:
		{
			input.type = RawInput::TYPE::RELEASE;
				mgr->m_keyState[key] = GH_STATE_RELEASED;
				mgr->rawInputs.push_back(input);
				_DEBUG("rawInput registered : [KEYBOARD] [" << RawInput::toString(input.type) << "]", LOG_CHANNEL::INPUT);
			break;
		}
		}
    });

    glfwSetCursorPosCallback(gPlatform().getWindow(), [](GLFWwindow *window, double xpos, double ypos)
    {
		InputManager *mgr = static_cast<InputManager*> (glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = RawInput::SOURCE::MOUSE;
		input.type = RawInput::TYPE::MOVE;
		input.data.move.x = xpos;
		input.data.move.y = ypos;

		mgr->rawInputs.push_back(input);
    });

    glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods)
    {
		InputManager *mgr = static_cast<InputManager*> (glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = RawInput::SOURCE::MOUSE;
		input.data.button.key = button;
		input.data.button.scancode = button;
		input.data.button.mods = mods;

		switch (action) {
		case GLFW_PRESS:
			input.type = RawInput::TYPE::PRESS;
				mgr->m_keyState[button] = GH_STATE_PRESSED;
				mgr->rawInputs.push_back(input);
			break;
		case GLFW_RELEASE:
			input.type = RawInput::TYPE::RELEASE;
				mgr->m_keyState[button] = GH_STATE_RELEASED;
				mgr->rawInputs.push_back(input);
			break;
		}
    });

	glfwSetScrollCallback(gPlatform().getWindow(), [](GLFWwindow *window, double offsetX, double offsetY) {
		InputManager *mgr = static_cast<InputManager*> (glfwGetWindowUserPointer(gPlatform().getWindow()));
		rawInput input;
		input.idx = 0;
		input.timestamp = 0;
		input.source = RawInput::SOURCE::MOUSE;
		input.type = RawInput::TYPE::RANGE;
		input.data.range.x = offsetX;
		input.data.range.y = offsetY;
		input.data.range.z = 0;
		mgr->rawInputs.push_back(input);
	});

    gEvent().addListener(GH_HASH("__GH_EVENT_JOYSTICK_STATE_CHANGE"), [](Event* e) {
        /*if(e->getJoystickState() == 1) {
            _DEBUG("Joystick [" << e->getJoystickIndex() << "] connected", LOG_CHANNEL::DEFAULT);
        } else {
            _DEBUG("Joystick [" << e->getJoystickIndex() << "] disconnected", LOG_CHANNEL::DEFAULT);
        }*/
    });

    /**
     * Add default input detection to exit the game when ESC is pressed
     */
    unique_ptr<InputContext> inputContext = make_unique<InputContext>(GH_HASH("__GH_INPUT_CONTEXT_SYSTEM"));
    int id = inputContext->getId();
    InputMatch *inputMatch = new InputMatch();
    inputMatch->source = RawInput::SOURCE::KEYBOARD;
    inputMatch->type = RawInput::TYPE::PRESS;
    inputMatch->key = (RawInput::KEY)GH_BUTTON_KEY_ESCAPE;
    inputMatch->callbackNameHash = GH_HASH("GH_ESCAPE_GAME");
    inputContext->registerMatch(unique_ptr<InputMatch>(inputMatch));

    this->registerInputCallback(GH_HASH("__GH_INPUT_EXIT_GAME"), []() {
		gApp().shutdown();
    });

    this->registerInputContext(move(inputContext));
    this->activeContext(id, true);

    /**
     * Read and configuration from conf object
     */
    if (m_bConfigurationOnInitialize) {
		vector<unique_ptr<InputContext>> &ictxs = m_config->getInputContexts();
		for (int i = 0; i < ictxs.size(); i++) {
			int id = (ictxs[i])->getId();
			unique_ptr<InputContext> ptr{move(ictxs[i])};
			ptr->setActive(true);
			m_inputContexts.insert(pair<int, unique_ptr<InputContext>>(id, move(ptr)));
		}
    }
    m_config = nullptr;
    _DEBUG("InputManager initialized", LOG_CHANNEL::INPUT);
}

void InputManager::vDestroy()
{
    _DEBUG("InputManager destroyed", LOG_CHANNEL::INPUT);
}

void InputManager::activeContext(int id, bool active)
{
    auto iter = m_inputContexts.find(id);
    if (iter != m_inputContexts.end()) {
	iter->second->setActive(active);
    } else {

	_ERROR("Cannot active the inputContext with the give id : " << id, LOG_CHANNEL::INPUT);
    }
}

void InputManager::registerInputContext(unique_ptr<InputContext> inputContext)
{
    auto iter = m_inputContexts.find(inputContext->getId());
    if (iter != m_inputContexts.end()) {

	_ERROR("Cannot add an inputContext already present in the InputManager", LOG_CHANNEL::INPUT);
    }
    m_inputContexts.insert(make_pair(inputContext->getId(), move(inputContext)));
}

void InputManager::registerInputCallback(U32 callbackHash, function<void(void) > callback)
{

    m_inputCallbacks.insert(make_pair(callbackHash, callback));
}

void InputManager::update()
{
    /**
     * Detection of held key, i dont rely on GLFW action repeat because
     * of the delay between press and the firist triggered hold input
     */
    for (int i = 0; i < GH_BUTTON_ARRAY_SIZE; i++) {
	if (m_keyState[i] == GH_STATE_PRESSED) {
	    m_keyState[i] == GH_STATE_HELD;
	    _DEBUG("HOLD KEY", LOG_CHANNEL::INPUT);
	} else if (m_keyState[i] == GH_STATE_HELD) {

	    _DEBUG("HOLD KEY", LOG_CHANNEL::INPUT);
	}
    }

    glfwPollEvents();
    detectChords();
    detectPlainInputs();
    rawInputs.clear();
}

void InputManager::detectChords()
{
    for (auto const &entry : m_inputContexts) {
	InputContext &context = (*entry.second);
	if (context.isActive()) {

	}
    }
}

void InputManager::detectPlainInputs()
{
    for (rawInput &input : rawInputs) {
	for (auto const &entry : m_inputContexts) {
	    InputContext &context = (*entry.second);
	    if (context.isActive()) {
		U32 callbackId;
		if (context.getInputMatch(input, &callbackId)) {
		    auto iter = m_inputCallbacks.find(callbackId);
		    if (iter != m_inputCallbacks.end()) {
			_DEBUG("INPUT MATCH TRIGERRED", LOG_CHANNEL::INPUT);
			iter->second();
		    } else {
			_WARNING("Input detected but no callback to call", LOG_CHANNEL::INPUT);
		    }
		}
	    }
	}
    }
}


InputManager&(*gInput)() = &InputManager::get;
}

