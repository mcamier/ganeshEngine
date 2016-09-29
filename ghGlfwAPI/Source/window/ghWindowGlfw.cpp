#include "window/ghWindowGlfw.hpp"

#include <GLFW/glfw3.h>
#include <util/ghILogger.hpp>
#include <sstream>

namespace ganeshEngine {

WindowGlfw::WindowGlfw() :
        IWindow(0),
        mpWindow{nullptr},
        mpMonitor{nullptr},
        mName(std::string("GaneshEngine Window")),
        mWidth(640),
        mHeight(480),
        mbFullscreen(false),
        mRefreshRate(60) {}

WindowGlfw::WindowGlfw(int width, int height, const std::string& name, bool isFullscreen) :
    IWindow(0),
    mpWindow{nullptr},
    mpMonitor{nullptr},
    mName(name),
    mWidth(width),
    mHeight(height),
    mbFullscreen(isFullscreen),
    mRefreshRate(60) {}

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
        _DEBUG("Platform initialized", LOG_CHANNEL::DEFAULT);
    }
    else {
        _ERROR("ERROR ON GLFW INIT DURING Platform INIT", LOG_CHANNEL::DEFAULT);
    }
}

void WindowGlfw::vDestroy() {
    glfwDestroyWindow(mpWindow);
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

}
