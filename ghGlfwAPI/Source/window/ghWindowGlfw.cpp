#include "window/ghWindowGlfw.hpp"

#include <GLFW/glfw3.h>
#include <util/ghILogger.hpp>
#include <sstream>

namespace ganeshEngine {

WindowGlfw::WindowGlfw() :
        IWindow(0),
        mpWindow{nullptr},
        mName(std::string("GaneshEngine Window")),
        mWidth(640),
        mHeight(480) { }

WindowGlfw::~WindowGlfw() {}

void WindowGlfw::vInitialize() {
    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mpWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL);
        if (mpWindow) {
            glfwSetErrorCallback([](int error, const char *message) {
                _ERROR("GLFW ERROR : code " << error << " message : " << message, LOG_CHANNEL::DEFAULT);
            });
            glfwMakeContextCurrent(mpWindow);
        } else {
            _ERROR("ERROR ON WINDOW CREATION", LOG_CHANNEL::DEFAULT);
        }
        _DEBUG("Platform initialized", LOG_CHANNEL::DEFAULT);
    }
    else {
        _ERROR("ERROR ON GLFW INIT DURING Platform INIT", LOG_CHANNEL::DEFAULT);
    }
}

void WindowGlfw::vDestroy() {

}

void WindowGlfw::setName(const std::string& newName) {
    mName = newName;
    glfwSetWindowTitle(mpWindow, mName.c_str());
}

std::string WindowGlfw::getName() {
    return mName;
}

bool WindowGlfw::isFullscreen() {
    //TODO implement
    return false;

}

void WindowGlfw::setFullscreen(bool isFullscreen) {
    //TODO implement
}

}
