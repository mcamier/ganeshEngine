#ifndef GANESHENGINE_WINDOWGLFW_H
#define GANESHENGINE_WINDOWGLFW_H

#include <window/ghIWindow.hpp>
#include <GLFW/glfw3.h>
#include <string>

namespace ganeshEngine {

class ghWindowGlfw : public IWindow {

private:
    GLFWwindow *mpWindow{nullptr};

public:
    ghWindowGlfw();

    ~ghWindowGlfw();

    void vInitialize();

    void vDestroy();

    void setName(const std::string& newName);

    std::string getName();

    bool isFullscreen();

    void setFullscreen(bool isFullscreen);
};

}

#endif