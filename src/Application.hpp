#ifndef RENDERENGINEPLAYGROUND_APPLICATION_HPP
#define RENDERENGINEPLAYGROUND_APPLICATION_HPP

#include "window/WindowManager.hpp"
#include "render/VulkanContextManager.hpp"
#include "input/InputManager.hpp"
#include "common/clock.hpp"

namespace rep
{

class Application
{

private:
    Clock clock;

public:
    Application() = default;

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    void run();

private:
    void init();

    void destroy();

protected:
    virtual void vInit() = 0;

    virtual void vUpdate() = 0;

    virtual void vDestroy() = 0;
};

}
#endif //RENDERENGINEPLAYGROUND_APPLICATION_HPP
