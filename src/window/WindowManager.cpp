#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "WindowManager.hpp"
#include "../common/logger.hpp"

#include <iostream>

namespace rep
{

void WindowManager::vInit(WindowManagerInitializeArgs_t initArgs)
{
    this->windowName = (initArgs.windowName != nullptr) ? initArgs.windowName : "Window Name";
    this->windowWidth = (initArgs.windowWidth > 0) ? initArgs.windowWidth : static_cast<uint16_t>(800);
    this->windowHeight = (initArgs.windowHeight > 0) ? initArgs.windowHeight : static_cast<uint16_t>(600);

    if (!glfwInit())
    {
        throw std::runtime_error("glfwInit failed");
    }

    // deactivate GL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->pWindow = glfwCreateWindow(this->windowWidth,
                                     this->windowHeight,
                                     this->windowName.c_str(),
                                     nullptr,
                                     nullptr);
    if (!this->pWindow)
    {
        throw std::runtime_error("glfwCreateWindow failed");
    }

    this->initInputCallbacks();
    REP_DEBUG("WindowManager initialized", LOG_CHANNEL::RENDER)
}


void WindowManager::vUpdate()
{
}


void WindowManager::vDestroy()
{
    glfwDestroyWindow(this->pWindow);
    glfwTerminate();
    REP_DEBUG("WindowManager destroyed", LOG_CHANNEL::RENDER)
}


void WindowManager::poolEvent()
{
    glfwPollEvents();
}


bool WindowManager::shouldClose()
{
    return glfwWindowShouldClose(this->pWindow) != 0;
}

void WindowManager::initInputCallbacks()
{
    glfwSetWindowCloseCallback(this->pWindow, [](GLFWwindow* window) {
    });

    glfwSetKeyCallback(this->pWindow, [](GLFWwindow *window, int key, int scancde, int action, int mods) {
    });

    glfwSetCursorPosCallback(this->pWindow, [](GLFWwindow *window, double xpos, double ypos) {
    });

    glfwSetMouseButtonCallback(this->pWindow, [](GLFWwindow *window, int button, int action, int mods) {
    });

    glfwSetScrollCallback(this->pWindow, [](GLFWwindow *window, double offsetX, double offsetY) {
    });
}

GLFWwindow* const WindowManager::getWindowHandle()
{
    return this->pWindow;
}

}