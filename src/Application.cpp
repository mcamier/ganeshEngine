#include "Application.hpp"
#include <array>
#include <chrono>

#include "common/profiler.hpp"

using namespace std::chrono;

namespace rep
{

void Application::run()
{
    this->init();

    while (!WindowManager::get().shouldClose())
    {
        WindowManager::get().vUpdate();

        this->vUpdate();
        // InputManager should be called last because it reset its state before the next frame
        // Try to detect inputs after this call will never detect anything
        InputManager::get().vUpdate();

        // rendering is called at fixed rate
        VulkanContextManager::get().vUpdate();
        // profiler doesn't need to e updated too often, so it's updated at fixed rate
        ProfilerManager::get().vUpdate();
    }

    this->destroy();
}

void Application::init()
{
    WindowManagerInitializeArgs_t windowManagerInitArgs = {};
    windowManagerInitArgs.windowName = "Vulkan Window";
    windowManagerInitArgs.windowWidth = 800;
    windowManagerInitArgs.windowHeight = 600;

    auto requiredExtension = getRequiredExtensions();
    std::array<const char *, 1> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};

    VulkanContextManagerInitializeArgs_t renderManagerInitArgs = {};
    renderManagerInitArgs.deviceExtensionCount = static_cast<uint32_t>(requiredExtension.size());
    renderManagerInitArgs.ppDeviceExtensions = requiredExtension.data();
    renderManagerInitArgs.validationLayerCount = static_cast<uint32_t>(validationLayers.size());
    renderManagerInitArgs.ppValidationLayersCount = validationLayers.data();
    renderManagerInitArgs.validationLayerEnabled = true;

    LoggerManagerInitializeArgs_t loggerManagerInitArgs = {};
    loggerManagerInitArgs.fileLogEnabled = true;
    loggerManagerInitArgs.fileLogBaseName = "log";
    loggerManagerInitArgs.fileLogFolder = "C:/Users/Mickael/Documents/workspace/renderEnginePlayground/cmake-build-debug";
    loggerManagerInitArgs.consoleLogEnabled = true;
    loggerManagerInitArgs.logLevel = LogLevelBitsFlag::DEBUG;
    loggerManagerInitArgs.logChannel = LogChannelBitsFlag::DEFAULT | LogChannelBitsFlag::RENDER;


    ProfilerManagerInitializeArgs_t profilerManagerInitArgs = {};
    InputManagerInitializeArgs_t inputManagerInitArgs = {};
    VulkanMemoryManagerInitializeArgs_t vkMemManagerInitializeArgs = {};
    vkMemManagerInitializeArgs.poolSize = 3;
    vkMemManagerInitializeArgs.chunkSize = 256000000;

    LoggerManager::initialize(loggerManagerInitArgs);
    ProfilerManager::initialize(profilerManagerInitArgs);

    BEGIN_PROFILING("All Managers Init")
        WindowManager::initialize(windowManagerInitArgs);
        InputManager::initialize(inputManagerInitArgs);
        VulkanContextManager::initialize(renderManagerInitArgs);
        VulkanMemoryManager::initialize(vkMemManagerInitializeArgs);
    END_PROFILING

    this->vInit();
}

void Application::destroy()
{
    this->vDestroy();
    VulkanMemoryManager::destroy();
    VulkanContextManager::destroy();
    InputManager::destroy();
    WindowManager::destroy();

    ProfilerManager::destroy();
    LoggerManager::destroy();
}

}
