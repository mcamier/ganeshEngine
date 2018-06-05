#include "Application.hpp"
#include <iostream>
#include <array>
#include <chrono>

#include "common/vulkan/vulkan_helpers.hpp"
#include "common/logger.hpp"
#include "common/profiler.hpp"
#include "window/WindowManager.hpp"
#include "render/RenderManager.hpp"


namespace rep
{

void Application::run()
{
    this->init();
    this->vInit();

    while (!WindowManager::get().shouldClose())
    {
        WindowManager::get().poolEvent();
        ProfilerManager::get().vUpdate();

        this->vUpdate();
        //RenderManager::get().vUpdate();
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
    std::array<const char*, 1> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };

    RenderManagerInitializeArgs_t renderManagerInitArgs = {};
    renderManagerInitArgs.deviceExtensionCount = static_cast<uint32_t>(requiredExtension.size());
    renderManagerInitArgs.ppDeviceExtensions = requiredExtension.data();
    renderManagerInitArgs.validationLayerCount = static_cast<uint32_t>(validationLayers.size());
    renderManagerInitArgs.ppValidationLayersCount = validationLayers.data();

    LoggerManagerInitializeArgs_t loggerManagerInitArgs = {};
    loggerManagerInitArgs.fileLogEnabled = true;
    loggerManagerInitArgs.fileLogBaseName = "log";
    loggerManagerInitArgs.fileLogFolder = "C:/Users/Mickael/Documents/workspace/renderEnginePlayground/cmake-build-debug";
    loggerManagerInitArgs.consoleLogEnabled = true;
    loggerManagerInitArgs.logLevel = LOG_LEVEL::DEBUG;
    loggerManagerInitArgs.logChannel = LOG_CHANNEL::DEFAULT | LOG_CHANNEL::RENDER;

    ProfilerManagerInitializeArgs_t profilerManagerInitArgs = {};

    LoggerManager::initialize(loggerManagerInitArgs);
    ProfilerManager::initialize(profilerManagerInitArgs);

    BEGIN_PROFILING("All Managers Init")
    WindowManager::initialize(windowManagerInitArgs);
    RenderManager::initialize(renderManagerInitArgs);
    END_PROFILING
}

void Application::destroy()
{
    this->vDestroy();
    RenderManager::destroy();
    WindowManager::destroy();

    ProfilerManager::destroy();
    LoggerManager::destroy();
}

}
