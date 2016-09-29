#ifndef GANESHENGINE_WINDOWGLFW_H
#define GANESHENGINE_WINDOWGLFW_H

#include <window/ghIWindow.hpp>
#include <GLFW/glfw3.h>
#include <string>

namespace ganeshEngine {

class WindowGlfw : public IWindow {

private:
    GLFWwindow *mpWindow;

    std::string mName;

    int mWidth;

    int mHeight;

public:
    WindowGlfw();

    ~WindowGlfw();

    void vInitialize();

    void vDestroy();

    void setName(const std::string& newName);

    std::string getName();

    bool isFullscreen();

    void setFullscreen(bool isFullscreen);
};

}

#endif