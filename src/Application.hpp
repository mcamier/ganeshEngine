#ifndef RENDERENGINEPLAYGROUND_APPLICATION_HPP
#define RENDERENGINEPLAYGROUND_APPLICATION_HPP

#include "window/WindowManager.hpp"
#include "render/RenderManager.hpp"
#include "common/clock.hpp"

namespace rep
{

class Application
{

private:
    Clock clock;

public:
    void run();

private:

    void init();

    void clean();

};

}
#endif //RENDERENGINEPLAYGROUND_APPLICATION_HPP
