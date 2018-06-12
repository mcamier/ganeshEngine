#include "VulkanContextManager.hpp"

#include <array>
#include <cassert>

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>

#include "../window/WindowManager.hpp"

namespace rep
{

void VulkanContextManager::vInit(VulkanContextManagerInitializeArgs_t args)
{
    initVulkanInstance(args);
    REP_DEBUG("  instance initialized", LOG_CHANNEL::RENDER);

    createSurface(this->vulkanInstance,
                  WindowManager::get().getWindowHandle(),
                  &this->surface);
    REP_DEBUG("  surface initialized", LOG_CHANNEL::RENDER);

    std::array<const char *, 1> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    pickPhysicalDevice(this->vulkanInstance,
                       this->surface,
                       static_cast<uint16_t>(deviceExtensions.size()),
                       deviceExtensions.data(),
                       &this->physicalDevice);
    REP_DEBUG("  physical device selected", LOG_CHANNEL::RENDER);

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice, this->surface);

    createLogicalDevice(this->physicalDevice,
                        indices,
                        args.validationLayerCount,
                        args.ppValidationLayersCount,
                        static_cast<uint32_t>(deviceExtensions.size()),
                        deviceExtensions.data(),
                        &this->device);
    REP_DEBUG("  logical device initialized", LOG_CHANNEL::RENDER);

    this->initAsyncObjects();
    REP_DEBUG("  async objects initialized", LOG_CHANNEL::RENDER);

    vkGetDeviceQueue(this->device, indices.graphicsFamily, 0, &this->graphicQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily, 0, &this->presentQueue);

    this->initSwapchain();
    REP_DEBUG("  swapchain initialized", LOG_CHANNEL::RENDER);

    createRenderPass(this->physicalDevice,
                     this->device,
                     this->swapchainImageFormat,
                     &this->renderPass);
    REP_DEBUG("  renderpass initialized", LOG_CHANNEL::RENDER);

    createCommandPool(this->physicalDevice,
                      this->device,
                      indices.graphicsFamily,
                      &this->graphicCommandPool);
    REP_DEBUG("  command pool initialized", LOG_CHANNEL::RENDER);

    /*
    this->initDepthTest();
    REP_DEBUG("  depth test initialized", LOG_CHANNEL::RENDER);
*/

    REP_DEBUG("RenderManager initialized", LOG_CHANNEL::RENDER)
}

vulkanContextInfos_t VulkanContextManager::getContextInfos()
{
    return {
            this->vulkanInstance,
            this->surface,
            this->physicalDevice,
            this->device,
            this->graphicQueue,
            this->presentQueue,
            this->graphicCommandPool,
            this->renderPass,
            this->swapchain
    };
}

void VulkanContextManager::initVulkanInstance(VulkanContextManagerInitializeArgs_t args)
{
    REP_DEBUG("RenderManager initialization...", LOG_CHANNEL::RENDER)

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
    else if (args.validationLayerEnabled)
    {
        if (!isValidationLayerSupported(args.validationLayerCount, args.ppValidationLayersCount))
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        else
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(args.validationLayerCount);
            createInfo.ppEnabledLayerNames = args.ppValidationLayersCount;
        }
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
    REP_DEBUG("  vulkan instance initialized", LOG_CHANNEL::RENDER);

    if (args.validationLayerEnabled)
    {
        /**
         * Setup callback method for validation layer
         */
        VkDebugReportCallbackCreateInfoEXT callbackCreateInfo = {};
        callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        callbackCreateInfo.pfnCallback = debugCallback;

        if (VK_SUCCESS !=
            createDebugReportCallbackEXT(this->vulkanInstance, &callbackCreateInfo, nullptr,
                                         &this->debugReportCallback))
        {
            throw std::runtime_error("Callback for validation layer failed");
        }
        REP_DEBUG("  debug callback initialized", LOG_CHANNEL::RENDER);
    }
}


void VulkanContextManager::destroyVulkanInstance()
{
    if (this->debugReportCallback)
    {
        destroyDebugReportCallbackEXT(this->vulkanInstance, this->debugReportCallback, nullptr);
    }
    vkDestroyInstance(this->vulkanInstance, nullptr);
}


void VulkanContextManager::initSwapchain()
{
    VkResult result;
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(this->physicalDevice,
                                                                     this->surface);
    this->swapchainExtent = chooseSwapExtent(swapChainSupport.capabilities, 800, 600);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    this->swapchainImageFormat = surfaceFormat.format;

    VkPresentModeKHR presentMode = chooseSwapPresentationMode(swapChainSupport.presentModes);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    /**
     * creating swapchain
     */
    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = this->surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = this->swapchainImageFormat;
    createInfo.imageExtent = this->swapchainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice,
                                                   this->surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};
    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
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


    result = vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, nullptr);
    assert(result == VK_SUCCESS);
    REP_DEBUG("Image amount detected for swapchain is : " << imageCount, LOG_CHANNEL::RENDER)

    this->swapchainImages.resize(imageCount);
    result = vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, this->swapchainImages.data());
    assert(result == VK_SUCCESS);

    /**
     * create swapchain image views
     */
    swapchainImageViews.resize(swapchainImages.size());
    for (size_t i = 0; i < swapchainImageViews.size(); i++)
    {
        this->swapchainImageViews[i] = createImageView(this->device,
                                                       this->swapchainImages[i],
                                                       swapchainImageFormat,
                                                       VK_IMAGE_ASPECT_COLOR_BIT);
    }
    REP_DEBUG("create " << swapchainImageViews.size() << " image views for the swapchain", LOG_CHANNEL::RENDER)
}


void VulkanContextManager::updateSwapchain()
{
    //vkDeviceWaitIdle(this->device);
}


void VulkanContextManager::destroySwapchain()
{
    for (auto &imageView : this->swapchainImageViews)
    {
        vkDestroyImageView(this->device, imageView, nullptr);
    }
    vkDestroySwapchainKHR(this->device, this->swapchain, nullptr);
}


void VulkanContextManager::destroyFramebuffers()
{
    for (auto framebuffer : this->swapChainFramebuffers)
    {
        vkDestroyFramebuffer(device,
                             framebuffer,
                             nullptr);
    }
}


void VulkanContextManager::initDepthTest()
{
    VkFormat depthFormat = findDepthFormat(this->physicalDevice);

    createImage(this->device,
                this->physicalDevice,
                this->swapchainExtent.width,
                this->swapchainExtent.height,
                depthFormat,
                VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                this->depthImage,
                this->depthImageMemory);

    this->depthImageView = createImageView(this->device,
                                           this->depthImage,
                                           depthFormat,
                                           VK_IMAGE_ASPECT_DEPTH_BIT);
    transitionImageLayout(this->device,
                          this->graphicCommandPool,
                          this->graphicQueue,
                          this->depthImage,
                          depthFormat,
                          VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}


void VulkanContextManager::destroyDepthTest()
{
    vkFreeMemory(this->device, this->depthImageMemory, nullptr);
    vkDestroyImageView(this->device, this->depthImageView, nullptr);
    vkDestroyImage(this->device, this->depthImage, nullptr);
}


void VulkanContextManager::initFramebuffers()
{
    size_t size = this->swapchainImageViews.size();
    this->swapChainFramebuffers.resize(size);

    for (size_t i = 0; i < size; i++)
    {
        std::array<VkImageView, 2> attachments[] = {
                this->swapchainImageViews[i],
                depthImageView
        };

        VkFramebufferCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        createInfo.renderPass = renderPass;
        createInfo.attachmentCount = static_cast<uint32_t>(attachments->size());
        createInfo.pAttachments = attachments->data();
        createInfo.width = this->swapchainExtent.width;
        createInfo.height = this->swapchainExtent.height;
        createInfo.layers = 1;

        if (VK_SUCCESS != vkCreateFramebuffer(this->device, &createInfo, nullptr, &this->swapChainFramebuffers[i]))
        {
            throw std::runtime_error("failed to create framebuffers");
        }
        REP_WARNING("  framebuffer is initialized", LOG_CHANNEL::RENDER)
    }
}

VkExtent2D VulkanContextManager::getCurrentExtent()
{
    return swapchainExtent;
}

VkImageView VulkanContextManager::getSwapchainImageView(uint32_t acquiredImage)
{
    return this->swapchainImageViews[acquiredImage];
}

void VulkanContextManager::vUpdate()
{
    vkDeviceWaitIdle(this->device);
}


void VulkanContextManager::initAsyncObjects()
{
    this->imageAvailableSemaphores.resize(MAX_CONCURRENT_FRAMES);
    this->renderFinishedSemaphores.resize(MAX_CONCURRENT_FRAMES);
    this->inFligtFences.resize(MAX_CONCURRENT_FRAMES);

    for (int i = 0; i < MAX_CONCURRENT_FRAMES; i++)
    {
        VkSemaphoreCreateInfo semaphoreImgAvailableInfo = {};
        semaphoreImgAvailableInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkSemaphoreCreateInfo semaphoreRenderDoneInfo = {};
        semaphoreRenderDoneInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        if (VK_SUCCESS !=
            vkCreateSemaphore(this->device, &semaphoreImgAvailableInfo, nullptr, &this->imageAvailableSemaphores[i]) ||
            VK_SUCCESS !=
            vkCreateSemaphore(this->device, &semaphoreRenderDoneInfo, nullptr, &this->renderFinishedSemaphores[i]) ||
            VK_SUCCESS !=
            vkCreateFence(this->device, &fenceInfo, nullptr, &this->inFligtFences[i]))
        {
            throw std::runtime_error("failed to create orchestration objects");
        }
    }
}

void VulkanContextManager::destroyAsyncObjects()
{
    for (int i = 0; i < MAX_CONCURRENT_FRAMES; i++)
    {
        vkDestroySemaphore(this->device, this->imageAvailableSemaphores[i], nullptr);
        vkDestroySemaphore(this->device, this->renderFinishedSemaphores[i], nullptr);
        vkDestroyFence(this->device, this->inFligtFences[i], nullptr);
    }
}

void VulkanContextManager::vDestroy()
{
    this->destroyAsyncObjects();
    this->destroyFramebuffers();
    this->destroyDepthTest();
    vkDestroyCommandPool(this->device, this->graphicCommandPool, nullptr);
    vkDestroyRenderPass(this->device, this->renderPass, nullptr);
    this->destroySwapchain();
    vkDestroyDevice(this->device, nullptr);
    this->destroyVulkanInstance();
    REP_DEBUG("RenderManager destroyed", LOG_CHANNEL::RENDER)
}

}