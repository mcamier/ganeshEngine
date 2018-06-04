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


void RenderManager::createSwapchain()
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(this->physicalDevice, this->surface);

    this->swapchainExtent = chooseSwapExtent(swapChainSupport.capabilities, 800, 600);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    this->swapchainImageFormat = surfaceFormat.format;
    VkPresentModeKHR presentMode = chooseSwapPresentationMode(swapChainSupport.presentModes);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 &&
        imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = this->surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = this->swapchainImageFormat;
    createInfo.imageExtent = this->swapchainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice, this->surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};
    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (VK_SUCCESS != vkCreateSwapchainKHR(this->device, &createInfo, nullptr, &this->swapchain))
    {
        throw std::runtime_error("swapchain creation failed");
    }

    vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, nullptr);
    this->swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, this->swapchainImages.data());
}


void RenderManager::updateSwapchain()
{
    vkDeviceWaitIdle(this->device);

    this->destroySwapchain();

    this->createSwapchain();
    //this->createImageViews();
    //this->createRenderPass();
    //this->createGraphicPipeline();
    //this->createDepthResources();
    //this->createFramebuffers();
    //this->createCommandBuffers();
}


void RenderManager::destroySwapchain()
{
    /*vkDestroyImageView(device, this->depthImageView, nullptr);
    vkDestroyImage(device, this->depthImage, nullptr);
    vkFreeMemory(device, this->depthImageMemory, nullptr);

    for (auto framebuffer : this->swapChainFramebuffers)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
    vkFreeCommandBuffers(this->device, this->commandPool, static_cast<uint32_t>(commandBuffers.size()),
                         commandBuffers.data());

    vkDestroyPipeline(this->device, this->pipeline, nullptr);
    vkDestroyPipelineLayout(this->device, this->pipelineLayout, nullptr);
    vkDestroyRenderPass(this->device, this->renderPass, nullptr);
    for (auto imageView : this->swapchainImageViews)
    {
        vkDestroyImageView(this->device, imageView, nullptr);
    }
    vkDestroySwapchainKHR(this->device, this->swapchain, nullptr);
     */
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