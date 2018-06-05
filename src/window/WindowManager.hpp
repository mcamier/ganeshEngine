#ifndef RENDERENGINEPLAYGROUND_WINDOWMANAGER_HPP
#define RENDERENGINEPLAYGROUND_WINDOWMANAGER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

#include "../common/managers.hpp"


namespace rep
{


struct WindowManagerInitializeArgs_t
{
    const char *windowName;
    uint16_t windowWidth;
    uint16_t windowHeight;
};


class WindowManager :
        public SingletonManager<WindowManager, WindowManagerInitializeArgs_t>
{
    friend SingletonManager<WindowManager, WindowManagerInitializeArgs_t>;
private:
    std::string windowName;
    uint16_t windowWidth;
    uint16_t windowHeight;
    GLFWwindow *pWindow;


protected:
    WindowManager() {}

    WindowManager(const WindowManager &) = delete;

    WindowManager &operator=(const WindowManager &) = delete;

    void vInit(WindowManagerInitializeArgs_t args) override;

    void vDestroy() override;

    void initInputCallbacks();

public:
    void vUpdate() override;

    void poolEvent();

    bool shouldClose();

    GLFWwindow* const getWindowHandle();

};

}

#endif //RENDERENGINEPLAYGROUND_WINDOWMANAGER_HPP
