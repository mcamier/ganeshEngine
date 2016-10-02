#include "window/ghWindowGlfw.hpp"

#include "window/ghInputGlfwUtils.hpp"
#include <util/ghILogger.hpp>
#include <event/ghEventManager.hpp>
#include <input/ghInputManager.hpp>

namespace ganeshEngine {

WindowGlfw::WindowGlfw() :
        IWindow(0),
        mpWindow{nullptr},
        mpMonitor{nullptr},
        mName(std::string("GaneshEngine Window")),
        mWidth(640),
        mHeight(480),
        mbFullscreen(false),
        mRefreshRate(60),
        mJoysticks(array<Joystick, GLFW_JOYSTICK_LAST>()){}

WindowGlfw::WindowGlfw(int width, int height, const std::string& name, bool isFullscreen) :
    IWindow(0),
    mpWindow{nullptr},
    mpMonitor{nullptr},
    mName(name),
    mWidth(width),
    mHeight(height),
    mbFullscreen(isFullscreen),
    mRefreshRate(60),
    mJoysticks(array<Joystick, GLFW_JOYSTICK_LAST>()) {}

WindowGlfw::~WindowGlfw() {}

void WindowGlfw::vInitialize() {
    if (glfwInit()) {
        mpMonitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        if(mbFullscreen) {
            mpWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), mpMonitor, nullptr);
        } else {
            mpWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), nullptr, nullptr);
        }

        if (mpWindow) {
            glfwSetErrorCallback([](int error, const char *message) {
                _ERROR("GLFW ERROR : code " << error << " message : " << message, LOG_CHANNEL::DEFAULT);
            });
            glfwMakeContextCurrent(mpWindow);
        } else {
            _ERROR("ERROR ON WINDOW CREATION", LOG_CHANNEL::DEFAULT);
        }

        for (int i = 0 ; i <= GLFW_JOYSTICK_LAST ; i++) {
            mJoysticks[i].initialize(i);
        }
        gEvent().addListener<WindowGlfw>(GH_EVENT_JOYSTICK_STATE_CHANGE, this, &WindowGlfw::onJoystickStateChange);

        glfwSetWindowCloseCallback(mpWindow, [](GLFWwindow* window) {
            gEvent().fireEvent(new Event(GH_EVENT_EXIT_GAME));
        });

        glfwSetJoystickCallback([](int joyIndex, int joyEvent) {
            gEvent().fireEvent(new JoystickStateChangeEvent(joyIndex, joyEvent));
        });

        glfwSetKeyCallback(mpWindow, [](GLFWwindow *window, int key, int scancde, int action, int mods) {
            if (action != GLFW_REPEAT) {
                RawInput input;
                input.idx = 0;
                input.source = InputSource::KEYBOARD;
                input.code = sysInputKeyboardCode2GHCode(key);
                if (action == GLFW_PRESS) input.type = InputType::BUTTON_PRESS;
                else if (action == GLFW_RELEASE) input.type = InputType::BUTTON_RELEASE;

                gInput().registerInput(input);
            }
        });

        glfwSetCursorPosCallback(mpWindow, [](GLFWwindow *window, double xpos, double ypos) {
            RawInput input;
            input.idx = 0;
            input.source = InputSource::MOUSE;
            input.type = InputType::AXIS;
            input.data.axis.x = (F32)xpos;
            input.data.axis.y = (F32)ypos;
            input.data.axis.z = 0.0f;

            gInput().registerInput(input);
        });

        glfwSetMouseButtonCallback(mpWindow, [](GLFWwindow *window, int button, int action, int mods) {
            if (action != GLFW_REPEAT) {
                RawInput input;
                input.idx = 0;
                input.source = InputSource::MOUSE;
                input.code = sysInputMouseCode2GHCode(button);
                if (action == GLFW_PRESS) input.type = InputType::BUTTON_PRESS;
                else if (action == GLFW_RELEASE) input.type = InputType::BUTTON_RELEASE;

                gInput().registerInput(input);
            }
        });

        glfwSetScrollCallback(mpWindow, [](GLFWwindow *window, double offsetX, double offsetY) {
            RawInput input;
            input.idx = 0;
            input.source = InputSource::MOUSE;
            input.type = InputType::AXIS;
            input.data.axis.x = (F32)offsetX;
            input.data.axis.y = (F32)offsetY;
            input.data.axis.z = 0.0f;

            gInput().registerInput(input);
        });
        
        _DEBUG("Platform initialized", LOG_CHANNEL::DEFAULT);
    }
    else {
        _ERROR("ERROR ON GLFW INIT DURING Platform INIT", LOG_CHANNEL::DEFAULT);
    }
}

void WindowGlfw::vDestroy() {
    glfwDestroyWindow(mpWindow);
}


void WindowGlfw::swapBuffer() {
    glfwSwapBuffers(mpWindow);
}

void WindowGlfw::pollEvents() {
    glfwPollEvents();

    for(auto device : mJoysticks) {
        device.update();
    }
}

void WindowGlfw::setName(const std::string& newName) {
    mName = newName;
    glfwSetWindowTitle(mpWindow, mName.c_str());
}

std::string WindowGlfw::getName() {
    return mName;
}

bool WindowGlfw::isFullscreen() {
    return mbFullscreen;

}

void WindowGlfw::setFullscreen(bool isFullscreen) {
    mbFullscreen = isFullscreen;
    if(mbFullscreen) {
        glfwSetWindowMonitor(mpWindow, mpMonitor, 0, 0, mWidth, mHeight, mRefreshRate);
    } else {
        glfwSetWindowMonitor(mpWindow, nullptr, 0, 0, mWidth, mHeight, mRefreshRate);
    }
}


void WindowGlfw::onJoystickStateChange(Event *event) {
    JoystickStateChangeEvent *jsce = static_cast<JoystickStateChangeEvent *>(event);
    int i = jsce->getJoystickIndex();
    if (i >= 0 || i <= GLFW_JOYSTICK_LAST) {
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

}
