#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <GLFW/glfw3.h>

namespace ganeshEngine {

    void InputManager::vInitialize() {
        glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
            rawInput input;
            input.idx = 0;
            input.timestamp = 0;
            input.source = RawInput::SOURCE::KEYBOARD;

            if(action == GLFW_PRESS) {
                input.type = RawInput::TYPE::PRESS;
            }else{
                input.type = RawInput::TYPE::RELEASE;
            }
            input.data.button.key = key;
            input.data.button.scancode = scancde;
            input.data.button.mods = mods;

            gInput().submitInput(input);
            //_TRACE("callback keyboard");
        });

        glfwSetCursorPosCallback(gPlatform().getWindow(), [](GLFWwindow *window, double xpos, double ypos) {
            rawInput input;
            input.idx = 0;
            input.timestamp = 0;
            input.source = RawInput::SOURCE::MOUSE;
            input.type = RawInput::TYPE::MOVE;
            input.data.move.x = xpos;
            input.data.move.y = ypos;

            gInput().submitInput(input);
        });

        glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
            rawInput input;
            input.idx = 0;
            input.timestamp = 0;
            input.source = RawInput::SOURCE::MOUSE;

            if(action == GLFW_PRESS) {
                input.type = RawInput::TYPE::PRESS;
            }else{
                input.type = RawInput::TYPE::RELEASE;
            }
            input.data.button.key = button;
            input.data.button.scancode = button;
            input.data.button.mods = mods;

            gInput().submitInput(input);
        });

        unique_ptr<InputContext> inputContext = make_unique<InputContext>();
        int id = inputContext->getId();
        unique_ptr<InputMatch> inputMatch = make_unique<InputMatch>();
        inputMatch->source = RawInput::SOURCE::KEYBOARD;
        inputMatch->type= RawInput::TYPE::PRESS;
        inputMatch->key = (RawInput::KEY)GH_BUTTON_KEY_ESCAPE;
        inputMatch->callbackNameHash = GH_HASH("GH_ESCAPE_GAME");
        inputContext->registerMatch(move(inputMatch));

        this->registerInputCallback(GH_HASH("GH_ESCAPE_GAME"), []() {
            gApp().shutdown();
        });

        /*, []() {
            gApp().shutdown();
        });*/
        this->registerInputContext(move(inputContext));
        this->activeContext(id, true);

        if(m_bConfigurationOnInitialize) {

        }
        _INFO("InputManager initialized", LOG_CHANNEL::INPUT);
    }


    void InputManager::vDestroy() {
        _INFO("InputManager destroyed", LOG_CHANNEL::INPUT);
    }

    void InputManager::activeContext(int id, bool active) {
        auto iter = inputContexts.find(id);
        if(iter != inputContexts.end()) {
            iter->second->setActive(active);
        } else {
            _ERROR("Cannot active the inputContext with the give id : " << id, LOG_CHANNEL::INPUT);
        }
    }

    void InputManager::submitInput(rawInput input) {
        rawInputs.push_back(input);
    }

    void InputManager::registerInputContext(unique_ptr<InputContext> inputContext) {
        auto iter = inputContexts.find(inputContext->getId());
        if(iter != inputContexts.end()) {
            _ERROR("Cannot add an inputContext already present in the InputManager", LOG_CHANNEL::INPUT);
        }
        inputContexts.insert(make_pair(inputContext->getId(), move(inputContext)));
    }

    void InputManager::registerInputCallback(U32 callbackHash, function<void(void)> callback) {
        m_inputCallbacks.insert(make_pair(callbackHash, callback));
    }

    void InputManager::update() {
        glfwPollEvents();
        for(rawInput &input : rawInputs) {

            for(auto const &entry : inputContexts) {
                InputContext &context = (*entry.second);
                if(context.isActive()){

                    int callbackId = context.contains(input);
                    /*
                     * TODO this check is really really unsafe because i'm assuming no hash could equals to 0
                     *      I need to modify this ASAP
                     */
                    if(callbackId != 0) {
                        auto iter = m_inputCallbacks.find(callbackId);
                        if(iter != m_inputCallbacks.end()){
                            _DEBUG("INPUT MATCH TRIGERRED", LOG_CHANNEL::INPUT);
                            iter->second();
                        } else {
                            _WARNING("Input detected but no callback to call", LOG_CHANNEL::INPUT)
                        }
                    }
                }
            }
        }
        rawInputs.clear();
    }

    InputManager&(*gInput)() = &InputManager::get;
}

