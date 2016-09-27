#include "window/ghWindowGlfw.hpp"

#include <GLFW/glfw3.h>
#include <util/ghILogger.hpp>
#include <sstream>

namespace ganeshEngine {

ghWindowGlfw::ghWindowGlfw() : IWindow(0) { }

ghWindowGlfw::~ghWindowGlfw() {}

void ghWindowGlfw::vInitialize() {
    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mpWindow = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
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


void ghWindowGlfw::setName(const std::string& newName) {
    //TODO implement
}

void ghWindowGlfw::vDestroy() {

}

std::string ghWindowGlfw::getName() {
    //TODO implement
    return "Awesome window";
}

bool ghWindowGlfw::isFullscreen() {
    //TODO implement
    return false;

}

void ghWindowGlfw::setFullscreen(bool isFullscreen) {
    //TODO implement
}

}
