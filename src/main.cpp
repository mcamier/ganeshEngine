#include <iostream>
#include <functional>

#include "Application.hpp"
#include "common/logger.hpp"

using namespace rep;


class Demo :
        public Application
{
protected:
    void vInit() override
    {
        REP_DEBUG("application demo initialized", LOG_CHANNEL::DEFAULT)
    }

    void vUpdate() override
    {

    }

    void vDestroy() override
    {
        REP_DEBUG("application demo destroyed", LOG_CHANNEL::DEFAULT)
    }
};


int main()
{
    Demo demo;
    try
    {
        demo.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}