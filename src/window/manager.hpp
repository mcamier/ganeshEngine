#ifndef GE_WINDOWMANAGER_HPP
#define GE_WINDOWMANAGER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

#include "../common/managers.hpp"


namespace ge
{
namespace window
{

// WindowManagerInitializeArgs_t gathers all properties that could be giving to the WindowManager during its
// initialization in order to customize its behavior
struct WindowManagerInitializeArgs_t
{
    const char *    windowName;
    uint16_t        windowWidth;
    uint16_t        windowHeight;
    bool            windowFullscreen;
};


// WindowManager is responsible for the glfw's window creation and forwarding window'sevent to the InputManager
//
// It's a singleton manager and should be accessed via get method
// Example:
//      WindowManager::get().vupdate();
class WindowManager :
        public SingletonManager<WindowManager, WindowManagerInitializeArgs_t>
{
    friend SingletonManager<WindowManager, WindowManagerInitializeArgs_t>;

private:
    GLFWwindow *    pWindow = nullptr;
    std::string     windowName;
    uint16_t        windowWidth = 0;
    uint16_t        windowHeight = 0;

protected:
    WindowManager() = default;

    // Initialize GLFW and then create the GLFW window
    void vInit(WindowManagerInitializeArgs_t args) override;

    void vDestroy() override;

    // Bind the GLFW's input callbacks to the InputManager
    void initInputCallbacks();

public:
    WindowManager(const WindowManager &) = delete;

    WindowManager &operator=(const WindowManager &) = delete;

    // Updating WindowManager is basically pooling last inputs from the window baked by GLFW
    void vUpdate() override;

    // Return TRUE if the user request the window to close
    bool shouldClose();

    // Return an handler on the GLFW window
    // Should not be used, except by the the VulkanContextManager which use it to create the rendering surface
    GLFWwindow* const getWindowHandle();

    // the the cursor at the center of the screen
    void setCursorAtCenter();

};

}
}

#endif //GE_WINDOWMANAGER_HPP
