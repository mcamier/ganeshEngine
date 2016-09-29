#ifndef GANESHENGINE_WINDOWGLFW_H
#define GANESHENGINE_WINDOWGLFW_H

#include <window/ghIWindow.hpp>
#include <util/ghClock.hpp>

#include <GLFW/glfw3.h>
#include <string>

namespace ganeshEngine {

class WindowGlfw : public IWindow {

private:
    GLFWwindow *mpWindow;

	GLFWmonitor *mpMonitor;

    std::string mName;

    int mWidth;

    int mHeight;

	bool mbFullscreen;

	int mRefreshRate;

public:
    WindowGlfw();

	WindowGlfw(int width, int height, const std::string& name, bool isFullscreen);

    ~WindowGlfw();

    void vInitialize() override;

    void vDestroy() override;

    void swapBuffer() override;

    void pollEvents() override;

    /**
     * @copydoc IWindow::setName(const std::string& newName)
     */
    void setName(const std::string& newName) override;

    /**
     * @copydoc IWindow::getName()
     */
    std::string getName() override;

    /**
     * @copydoc IWindow::isFullscreen()
     */
    bool isFullscreen() override;

    /**
     * @copydoc IWindow::setFullscreen(bool isFullscreen)
     */
    void setFullscreen(bool isFullscreen) override;
};

}

#endif