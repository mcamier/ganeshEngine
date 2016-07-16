#include "ghInputManager.h"
#include "ghApplication.h"
#include "ghPlatform.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ganeshEngine {

    void InputManager::vInitialize() {
        if( glfwInit() ) {
            glfwSetKeyCallback(gPlatform().getWindow(), [](GLFWwindow *window, int key, int scancde, int action, int mods) {
                rawInput input;
                input.source = rawInputSource::KEYBOARD;
                input.type = rawInputType::PRESS;
                input.type = rawInputType::RELEASE;
                input.timestamp = 0;
                input.data.keyboard.action = action;
                input.data.keyboard.key = key;
                input.data.keyboard.scancode = scancde;
                input.data.keyboard.mods = mods;
                gInput().registerInput(input);
                //_TRACE("callback keyboard");
            });

            glfwSetCursorPosCallback(gPlatform().getWindow(), [](GLFWwindow *window, double xpos, double ypos) {
                rawInput input;
                input.source = rawInputSource::MOUSE;
                input.type = rawInputType::MOVE;
                input.timestamp = 0;
                input.data.mouse.x = xpos;
                input.data.mouse.y = ypos;
                gInput().registerInput(input);
                //_TRACE("callback mouse cursor");
            });

            glfwSetMouseButtonCallback(gPlatform().getWindow(), [](GLFWwindow *window, int button, int action, int mods) {
                rawInput input;
                input.source = rawInputSource::MOUSE;
                input.type = rawInputType::PRESS;
                input.type = rawInputType::RELEASE;
                input.timestamp = 0;
                input.data.button.button = button;
                input.data.button.action = action;
                input.data.button.mods = mods;
                gInput().registerInput(input);
                //_TRACE("callback mouse button");
            });
            _INFO("InputManager initialized");
        }
        else {
            _FATAL("ERROR ON GLFW INIT DURING InputManager INIT");
        }
    }

    void InputManager::registerInput(rawInput input) {
        rawInputs.push_back(input);
    }

    void InputManager::vDestroy() {
        _INFO("InputManager destroyed");
    }

    void InputManager::update() {
        glfwPollEvents();
        _DEBUG("get " << rawInputs.size() << " inputs this frame");
        for(rawInput &input : rawInputs) {
            /*switch(input.source) {
                case rawInputSource::KEYBOARD:
                _DEBUG("\t keyboard");
                    break;
                case rawInputSource::MOUSE:
                _DEBUG("\t mouse move");
                    break;
                case rawInputSource::MOUSE_BUTTON:
                _DEBUG("\t mouse button");
                    break;
            }*/
        }
        rawInputs.clear();

        if(GLFW_PRESS == glfwGetKey(gPlatform().getWindow(), GLFW_KEY_ESCAPE)) {
            gApp().shutdown();
        }
    }

    InputManager&(*gInput)() = &InputManager::get;
}

