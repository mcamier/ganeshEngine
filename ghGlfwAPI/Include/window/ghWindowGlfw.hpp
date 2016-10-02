#ifndef GANESHENGINE_WINDOWGLFW_H
#define GANESHENGINE_WINDOWGLFW_H

#include <window/ghIWindow.hpp>
#include <util/ghClock.hpp>

#include <GLFW/glfw3.h>
#include <string>
#include <event/ghEvent.hpp>
#include "ghJoystick.hpp"

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

    /**
     * Maybe not the better place to put the joystick management but the window is still in charge of emitting events
     * and joystick event are no exception
     */
    array<Joystick, GLFW_JOYSTICK_LAST> mJoysticks;

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

    /**
     * Called when joystick get plugged or unplugged
     * @param event
     */
    void onJoystickStateChange(Event *event);
};

}

#endif