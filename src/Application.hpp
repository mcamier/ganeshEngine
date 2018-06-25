#ifndef RENDERENGINEPLAYGROUND_APPLICATION_HPP
#define RENDERENGINEPLAYGROUND_APPLICATION_HPP

#include "window/WindowManager.hpp"
#include "render/VulkanContextManager.hpp"
#include "input/InputManager.hpp"

namespace rep
{


// Application class is meant to be derived by another new class to implement a game application
// In order to start the application just have to call the run method, it will start the lifecycle of the
// game.
class Application
{

public:
    Application() = default;

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    // Entry point of the game application, it will initialize all the system, run the main loop and then
    // release resources when the application should close
    void run();

private:
    // Initialize all systems required like, the LoggerManager, ProfileManager, WindowManager, InputMananger,
    // VulkanContextManager and so on.
    // Also call the application's specific vInit method
    void init();

    // Destroy all systems initialized during the application start up
    // Also call the application's specific vDestroy method
    void destroy();

protected:
    // Can be override by the derivating class in order to do custom initialization
    virtual void vInit() = 0;

    // Can be override by the derivating class in order to update game application each frame
    virtual void vUpdate() = 0;

    // Should be override by the derivating class in order to release all resources created during the vInit call
    virtual void vDestroy() = 0;
};

}
#endif //RENDERENGINEPLAYGROUND_APPLICATION_HPP
