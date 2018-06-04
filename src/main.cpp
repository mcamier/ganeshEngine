#include <iostream>
#include <functional>

//#include "render/vulkanFunctions.hpp"
//#include "HelloTriangleApplication.hpp"
#include "Application.hpp"

/*
#ifdef _WIN32

    #include <Windows.h>

    #define LIBRARY_TYPE HMODULE
    #define LoadFunction GetProcAddress
#elif defined __linux
    #include <dlfcn.h>
    #define LIBRARY_TYPE void*
    #define LoadFunction dlsym
#endif

namespace rep
{


    void getVulkanLibHandler(LIBRARY_TYPE &vulkan_library)
    {
#ifdef _WIN32
        vulkan_library = LoadLibrary("vulkan-1.dll");
#elif defined __linux
        vulkan_library = dlopen("vulkan-1.so.1");
#endif

        if (nullptr == vulkan_library)
        {
            throw std::runtime_error("failed to get handler on vulkan dynamic library");
        }
    }

    void bindVulkanPointertoFunctions(LIBRARY_TYPE const &vulkan_library)
    {
#define EXPORTED_VULKAN_FUNCTION(function)\
    function = (PFN_##function) LoadFunction(vulkan_library, #function);\
    if((function) == nullptr){\
        throw std::runtime_error("failed to load vulkan function pointer");\
    }

#define GLOBAL_LEVEL_VULKAN_FUNCTION(function) \
    function = (PFN_##function) vkGetInstanceProcAddr(nullptr, #function);\
    if((function) == nullptr){\
        throw std::runtime_error("failed to load vulkan function pointer");\
    }

#define INSTANCE_LEVEL_VULKAN_FUNCTION(function)
#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)
#define DEVICE_LEVEL_VULKAN_FUNCTION(function)
#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)

#include "render/listVulkanFunctions.inc.hpp"
    }
}
*/

int main()
{
    /*LIBRARY_TYPE vulkan_library;
    try
    {
        rep::getVulkanLibHandler(vulkan_library);
        rep::bindVulkanPointertoFunctions(vulkan_library);
    } catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }*/


    rep::Application app;
    try
    {
        app.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

/*
  HelloTriangleApplication app;
    try
    {
        app.run();
    } catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
*/
    return EXIT_SUCCESS;
}