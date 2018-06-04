#include "RenderManager.hpp"

#include <array>

#include "../common/vulkan/vulkan_helpers.hpp"
#include "../window/WindowManager.hpp"

namespace rep
{

void RenderManager::vInit(RenderManagerInitializeArgs_t args)
{
    VkApplicationInfo appInfo = {};
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    /**
     * Activate if needed validation layers
     */
    if (args.validationLayerCount == 0)
    {
        createInfo.enabledLayerCount = 0;
    }
    else if (!isValidationLayerSupported(args.validationLayerCount, args.ppValidationLayersCount))
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    else
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(args.validationLayerCount);
        createInfo.ppEnabledLayerNames = args.ppValidationLayersCount;
    }
    /**
     * Set required extensions
     */
    createInfo.enabledExtensionCount = static_cast<uint32_t>(args.deviceExtensionCount);
    createInfo.ppEnabledExtensionNames = args.ppDeviceExtensions;
    /**
     * Instance creation
     */
    if (VK_SUCCESS != vkCreateInstance(&createInfo, nullptr, &this->vulkanInstance))
    {
        throw std::runtime_error("Create vulkan instance failed");
    }
    /**
     * Setup callback method for validation layer
     */
    VkDebugReportCallbackCreateInfoEXT callbackCreateInfo = {};
    callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    callbackCreateInfo.pfnCallback = debugCallback;

    if (VK_SUCCESS !=
        createDebugReportCallbackEXT(this->vulkanInstance, &callbackCreateInfo, nullptr, &this->debugReportCallback))
    {
        throw std::runtime_error("Callback for validation layer failed");
    }

    createSurface(this->vulkanInstance,
                  WindowManager::get().getWindowHandle(),
                  &this->surface);

    std::array<const char *, 1> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    pickPhysicalDevice(this->vulkanInstance,
                       this->surface,
                       static_cast<uint16_t>(deviceExtensions.size()),
                       deviceExtensions.data(),
                       &this->physicalDevice);

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice, this->surface);

    createLogicalDevice(this->physicalDevice,
                        indices,
                        args.validationLayerCount,
                        args.ppValidationLayersCount,
                        static_cast<uint32_t>(deviceExtensions.size()),
                        deviceExtensions.data(),
                        &this->device);

    vkGetDeviceQueue(this->device, indices.graphicsFamily, 0, &this->graphicQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily, 0, &this->presentQueue);

    createCommandPool(this->physicalDevice,
                      this->device,
                      indices,
                      &this->commandPool);
    REP_DEBUG("RenderManager initialized", LOG_CHANNEL::RENDER)
}


void RenderManager::vUpdate()
{
}


void RenderManager::vDestroy()
{
    vkDestroyCommandPool(this->device, this->commandPool, nullptr);
    vkDestroyDevice(this->device, nullptr);
    destroyDebugReportCallbackEXT(this->vulkanInstance, this->debugReportCallback, nullptr);
    vkDestroyInstance(this->vulkanInstance, nullptr);
    REP_DEBUG("RenderManager destroyed", LOG_CHANNEL::RENDER)
}

}