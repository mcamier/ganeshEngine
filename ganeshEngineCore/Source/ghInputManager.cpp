#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <GLFW/glfw3.h>

namespace ganeshEngine {

    void InputManager::vInitialize() {
        if( glfwInit() ) {
            glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
                rawInput input;
                input.idx = 0;
                input.timestamp = 0;
                input.source = rawInputSource::KEYBOARD;

                if(action == GLFW_PRESS) {
                    input.type = rawInputType::PRESS;
                }else{
                    input.type = rawInputType::RELEASE;
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
                input.source = rawInputSource::MOUSE;
                input.type = rawInputType::MOVE;
                input.data.move.x = xpos;
                input.data.move.y = ypos;

                gInput().submitInput(input);
            });

            glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
                rawInput input;
                input.idx = 0;
                input.timestamp = 0;
                input.source = rawInputSource::MOUSE;

                if(action == GLFW_PRESS) {
                    input.type = rawInputType::PRESS;
                }else{
                    input.type = rawInputType::RELEASE;
                }
                input.data.button.key = button;
                input.data.button.scancode = button;
                input.data.button.mods = mods;

                gInput().submitInput(input);
            });
            _INFO("InputManager initialized");

            unique_ptr<InputContext> inputContext = make_unique<InputContext>();
            int id = inputContext->getId();
            unique_ptr<InputMatch> inputMatch = make_unique<InputMatch>();;
            inputMatch->source = rawInputSource::KEYBOARD;
            inputMatch->type= rawInputType::PRESS;
            inputMatch->idx = 0;
            inputMatch->key = GLFW_KEY_ESCAPE;

            inputContext->registerMatch(move(inputMatch));
            this->registerInputContext(move(inputContext));
            this->activeContext(id, true);
        }
        else {
            _FATAL("ERROR ON GLFW INIT DURING InputManager INIT");
        }
    }

    void InputManager::activeContext(int id, bool active) {
        auto iter = inputContexts.find(id);
        if(iter != inputContexts.end()) {
            _ERROR("Cannot active the inputContext with the give id : " << id);
        }
        iter->second->setActive(active);
    }

    void InputManager::submitInput(rawInput input) {
        rawInputs.push_back(input);
    }

    void InputManager::vDestroy() {
        _INFO("InputManager destroyed");
    }

    void InputManager::registerInputContext(unique_ptr<InputContext> inputContext) {
        auto iter = inputContexts.find(inputContext->getId());
        if(iter != inputContexts.end()) {
            _ERROR("Cannot add an inputContext already present in the InputManager");
        }
        inputContexts.insert(make_pair(inputContext->getId(), move(inputContext)));
    }

    void InputManager::update() {
        glfwPollEvents();
        _DEBUG("get " << rawInputs.size() << " inputs this frame");
        for(rawInput &input : rawInputs) {

            for(auto const &entry : inputContexts) {
                InputContext &context = (*entry.second);
                if(context.isActive() && context.contains(input)) {

                    // TODO trigger callback or something else
                    // temporary piece of code
                    _DEBUG("INPUT MATCH TRIGERRED");
                    gApp().shutdown();
                }
            }
        }
        rawInputs.clear();
    }

    InputManager&(*gInput)() = &InputManager::get;
}

