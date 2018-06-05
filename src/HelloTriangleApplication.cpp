#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "HelloTriangleApplication.hpp"
#include <set>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <chrono>


void HelloTriangleApplication::run()
{
    this->initWindow();
    this->initVulkan();
    this->mainLoop();
    this->cleanup();
}


void HelloTriangleApplication::initWindow()
{
    if (!glfwInit())
    {
        throw std::runtime_error("glfwInit failed");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // deactivate GL context
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->pWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", nullptr, nullptr);
    if (!this->pWindow)
    {
        throw std::runtime_error("glfwCreateWindow failed");
    }
}


void HelloTriangleApplication::initVulkan()
{
    this->loadModel();
    this->createInstance();
#ifdef _DEBUG
    this->setupVulkanCallback();
#endif
    this->createSurface();
    this->pickPhysicalDevice();
    this->createLogicalDevice();
    this->createCommandPool();
    // swapchain and pipeline
    this->createSwapChain();
    this->createImageViews();
    this->createRenderPass();
    this->createDescriptorSetLayout();
    this->createGraphicPipeline();
    this->createDepthResources();
    this->createFramebuffers();
    this->createDescriptorpool();
    this->createDescriptorSet();
    // image
    this->createTextureImage();
    this->createTextureImageView();
    this->createTextureSampler();
    // geometry setup
    this->createVertexBuffer();
    this->createIndexBuffer();
    this->createUboBuffer();
    // draw command
    this->createCommandBuffers();
    // other
    this->createOrchestratorObjects();
}


void HelloTriangleApplication::mainLoop()
{
    while (!glfwWindowShouldClose(this->pWindow))
    {
        glfwPollEvents();
        updateUniformBuffer();
        drawFrame();
    }
    vkDeviceWaitIdle(this->device);
}

void HelloTriangleApplication::drawFrame()
{
    auto timeout = std::numeric_limits<uint64_t>::max();
    vkWaitForFences(this->device, 1, &this->inFligtFences[currentFrame], VK_TRUE, timeout);
    vkResetFences(this->device, 1, &this->inFligtFences[currentFrame]);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(this->device,
                                            this->swapchain,
                                            std::numeric_limits<uint64_t>::max(),
                                            imageAvailableSemaphores[currentFrame],
                                            VK_NULL_HANDLE,
                                            &imageIndex);

    if (VK_ERROR_OUT_OF_DATE_KHR == result)
    {
        this->recreateSwapChain();
        return;
    } else if (VK_SUCCESS != result && VK_SUBOPTIMAL_KHR != result)
    {
        throw std::runtime_error("failed to qcquire swap chain image");
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (VK_SUCCESS != vkQueueSubmit(this->graphicQueue, 1, &submitInfo, this->inFligtFences[currentFrame]))
    {
        throw std::runtime_error("failed to submit render commandbuffer for drawing");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {this->swapchain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(this->presentationQueue, &presentInfo);

    if (VK_ERROR_OUT_OF_DATE_KHR == result || VK_SUBOPTIMAL_KHR == result)
    {
        recreateSwapChain();
    } else if (VK_SUCCESS != result)
    {
        throw std::runtime_error("failed to present swapchain image");
    }

    currentFrame = (currentFrame + 1) % MAX_CONCURRENT_FRAMES;
}


void HelloTriangleApplication::cleanup()
{
    this->cleanupSwapchain();

    vkDestroySampler(this->device, this->textureSampler, nullptr);
    vkDestroyImageView(this->device, this->textureImageView, nullptr);
    vkDestroyImage(this->device, this->textureImage, nullptr);
    vkFreeMemory(this->device, this->textureImageMemory, nullptr);

    vkDestroyShaderModule(this->device, this->fragShaderModule, nullptr);
    vkDestroyShaderModule(this->device, this->vertShaderModule, nullptr);
    for (int i = 0; i < MAX_CONCURRENT_FRAMES; i++)
    {
        vkDestroySemaphore(this->device, this->imageAvailableSemaphores[i], nullptr);
        vkDestroySemaphore(this->device, this->renderFinishedSemaphores[i], nullptr);
        vkDestroyFence(this->device, this->inFligtFences[i], nullptr);
    }

    vkDestroyDescriptorPool(this->device, this->descriptorPool, nullptr);

    vkDestroyDescriptorSetLayout(this->device, this->descriptorSetLayout, nullptr);
    vkDestroyBuffer(this->device, this->vertexBuffer, nullptr);
    vkFreeMemory(this->device, this->vertexBufferMemory, nullptr);
    vkDestroyBuffer(this->device, this->indexBuffer, nullptr);
    vkFreeMemory(this->device, this->indexBufferMemory, nullptr);
    vkDestroyBuffer(this->device, this->uboBuffer, nullptr);
    vkFreeMemory(this->device, this->uboBufferMemory, nullptr);
    vkDestroyBuffer(this->device, this->textureImage, nullptr);
    vkFreeMemory(this->device, this->textureImageMemory, nullptr);

    vkDestroyCommandPool(this->device, this->commandPool, nullptr);
    vkDestroyDevice(this->device, nullptr);
#ifdef _DEBUG
    DestroyDebugReportCallbackEXT(this->vulkanInstance, this->callback, nullptr);
#endif
    vkDestroySurfaceKHR(this->vulkanInstance, this->surface, nullptr);
    vkDestroyInstance(this->vulkanInstance, nullptr);

    glfwDestroyWindow(this->pWindow);
    glfwTerminate();
}

void HelloTriangleApplication::cleanupSwapchain()
{
    vkDestroyImageView(device, this->depthImageView, nullptr);
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
}

#ifdef _DEBUG

bool HelloTriangleApplication::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : this->validationLayers)
    {
        bool layerFound = false;

        for (const VkLayerProperties &layerProp : availableLayers)
        {
            if (strcmp(layerName, layerProp.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}


void HelloTriangleApplication::setupVulkanCallback()
{
    VkDebugReportCallbackCreateInfoEXT createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;

    if (CreateDebugReportCallbackEXT(this->vulkanInstance, &createInfo, nullptr, &this->callback) != VK_SUCCESS)
    {
        throw std::runtime_error("Callback for validation layer failed");
    }
}

#endif


std::vector<const char *> HelloTriangleApplication::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions;
    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        extensions.push_back(glfwExtensions[i]);
    }

#ifdef _DEBUG
    extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
#endif

    return extensions;
}


bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices queueIndices = findQueueFamilies(device);
    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        SwapChainSupportDetails swapChainDetails = querySwapChainSupport(device);
        swapChainAdequate = !swapChainDetails.formats.empty() && !swapChainDetails.presentModes.empty();
    }

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader &&
           queueIndices.isComplete() &&
           extensionsSupported &&
           swapChainAdequate &&
           deviceFeatures.samplerAnisotropy;
}


void HelloTriangleApplication::createInstance()
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


#ifdef _DEBUG
    if (!checkValidationLayerSupport())
    {
        throw std::runtime_error("validation layers requested, but not available!");
    } else
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(this->validationLayers.size());
        createInfo.ppEnabledLayerNames = this->validationLayers.data();
    }
#else
    createInfo.enabledLayerCount = 0;
#endif

    std::vector<const char *> extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (VK_SUCCESS != vkCreateInstance(&createInfo, nullptr, &this->vulkanInstance))
    {
        throw std::runtime_error("Create vulkan instance failed");
    }
}


bool HelloTriangleApplication::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionsCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionsCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto &extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

void HelloTriangleApplication::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(this->vulkanInstance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(this->vulkanInstance, &deviceCount, devices.data());

    for (const VkPhysicalDevice &device : devices)
    {
        if (isDeviceSuitable(device))
        {
            this->physicalDevice = device;
            break;
        }
    }

    if (this->physicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}


void HelloTriangleApplication::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.presentFamily, indices.graphicsFamily};

    for (int queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();


#ifdef _DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
#else
    createInfo.enabledLayerCount = 0;
#endif

    if (VK_SUCCESS != vkCreateDevice(this->physicalDevice, &createInfo, nullptr, &this->device))
    {
        throw std::runtime_error("logical device creation failed");
    }

    vkGetDeviceQueue(this->device, indices.graphicsFamily, 0, &this->graphicQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily, 0, &this->presentationQueue);
}


void HelloTriangleApplication::createSurface()
{
    if (VK_SUCCESS != glfwCreateWindowSurface(this->vulkanInstance, this->pWindow, nullptr, &this->surface))
    {
        throw std::runtime_error("failed to create window surface!");
    }
}


QueueFamilyIndices HelloTriangleApplication::findQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const VkQueueFamilyProperties &queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, this->surface, &presentSupport);
        if (queueFamily.queueCount > 0 && presentSupport)
        {
            indices.presentFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }
        i++;
    }

    return indices;
}

SwapChainSupportDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice device)
{
    SwapChainSupportDetails details;
    uint32_t formatCount = 0;
    uint32_t presentModeCount = 0;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, this->surface, &details.capabilities);

    vkGetPhysicalDeviceSurfaceFormatsKHR(device, this->surface, &formatCount, nullptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, this->surface, &presentModeCount, nullptr);

    if (formatCount > 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, this->surface, &formatCount, details.formats.data());
    }

    if (presentModeCount > 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, this->surface, &presentModeCount,
                                                  details.presentModes.data());
    }
    return details;
}

VkSurfaceFormatKHR
HelloTriangleApplication::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
    {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }

    for (const auto &availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR
HelloTriangleApplication::chooseSwapPresentationMode(const std::vector<VkPresentModeKHR> &availableModes)
{
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

    for (const VkPresentModeKHR &availableMode : availableModes)
    {
        if (availableMode == VK_PRESENT_MODE_MAILBOX_KHR ||
            availableMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
        {
            bestMode = availableMode;
        }
    }
    return bestMode;
}

VkExtent2D HelloTriangleApplication::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    } else
    {
        VkExtent2D actualExtent = {WIDTH, HEIGHT};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void HelloTriangleApplication::createSwapChain()
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(this->physicalDevice);

    this->swapChainExtent = chooseSwapExtent(swapChainSupport.capabilities);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    this->swapChainImageFormat = surfaceFormat.format;
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
    createInfo.imageFormat = this->swapChainImageFormat;
    createInfo.imageExtent = this->swapChainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice);
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

void HelloTriangleApplication::recreateSwapChain()
{
    vkDeviceWaitIdle(this->device);

    this->cleanupSwapchain();

    this->createSwapChain();
    this->createImageViews();
    this->createRenderPass();
    this->createGraphicPipeline();
    this->createDepthResources();
    this->createFramebuffers();
    this->createCommandBuffers();
}

void HelloTriangleApplication::createImageViews()
{
    swapchainImageViews.resize(swapchainImages.size());
    for (size_t i = 0; i < swapchainImageViews.size(); i++)
    {
        this->swapchainImageViews[i] = createImageView(swapchainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}


VkShaderModule HelloTriangleApplication::createShaderModule(const std::vector<char> &code)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

    VkShaderModule shaderModule;
    if (VK_SUCCESS != vkCreateShaderModule(this->device, &createInfo, nullptr, &shaderModule))
    {
        throw std::runtime_error("failed to create shader module");
    }

    return shaderModule;
}


void HelloTriangleApplication::createGraphicPipeline()
{
    // shader module creation
    this->vertShaderModule = createShaderModule(readFile("../shaders/compiled/vert.spv"));
    this->fragShaderModule = createShaderModule(readFile("../shaders/compiled/frag.spv"));

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = this->vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = this->fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    // vertex input setup
    auto bindingDescription = VertexPosColorTex::getBindingDescription();
    auto attributeDescription = VertexPosColorTex::getAttributeDescriptions();
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexAttributeDescriptionCount = attributeDescription.size();
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescription.data();
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;

    // input assembly
    VkPipelineInputAssemblyStateCreateInfo assemblyStateInfo = {};
    assemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assemblyStateInfo.primitiveRestartEnable = VK_FALSE;
    assemblyStateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    // viewport and scissors
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) this->swapChainExtent.width;
    viewport.height = (float) this->swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = this->swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportInfo = {};
    viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = &scissor;
    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = &viewport;

    // rasterizer
    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.lineWidth = 1.0f;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    // multisampling
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // color blending
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    // pipeline layout
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &this->descriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (VK_SUCCESS != vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &this->pipelineLayout))
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    VkPipelineDepthStencilStateCreateInfo depthStencilInfo = {};
    depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilInfo.depthTestEnable = VK_TRUE;
    depthStencilInfo.depthWriteEnable = VK_TRUE;
    depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
    depthStencilInfo.minDepthBounds = 0.0f;
    depthStencilInfo.maxDepthBounds = 1.0f;
    depthStencilInfo.stencilTestEnable = VK_FALSE;
    depthStencilInfo.front = {};
    depthStencilInfo.back = {};

    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &assemblyStateInfo;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencilInfo;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr;
    pipelineInfo.layout = this->pipelineLayout;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->pipeline) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }
}

void HelloTriangleApplication::createRenderPass()
{
    VkAttachmentDescription depthAttachment = {};
    depthAttachment.format = findDepthFormat(this->physicalDevice);
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = this->swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentRef = {};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &this->renderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create render pass!");
    }
}

void HelloTriangleApplication::createFramebuffers()
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
        createInfo.width = swapChainExtent.width;
        createInfo.height = swapChainExtent.height;
        createInfo.layers = 1;

        if (VK_SUCCESS != vkCreateFramebuffer(this->device, &createInfo, nullptr, &this->swapChainFramebuffers[i]))
        {
            throw std::runtime_error("failed to create framebuffers");
        }
    }
}

void HelloTriangleApplication::createCommandPool()
{
    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice);

    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = indices.graphicsFamily;
    poolInfo.flags = 0;

    if (VK_SUCCESS != vkCreateCommandPool(device, &poolInfo, nullptr, &this->commandPool))
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

void HelloTriangleApplication::createCommandBuffers()
{
    this->commandBuffers.resize(this->swapChainFramebuffers.size());

    std::array<VkClearValue, 2> clearValues = {};
    clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = this->commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) this->commandBuffers.size();

    if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    for (size_t i = 0; i < this->commandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        if (VK_SUCCESS != vkBeginCommandBuffer(this->commandBuffers[i], &beginInfo))
        {
            throw std::runtime_error("failed to begin recording command buffer");
        }

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->renderPass;
        renderPassInfo.framebuffer = this->swapChainFramebuffers[i];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = this->swapChainExtent;
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(this->commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(this->commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, this->pipeline);

        vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1,
                                &descriptorSet, 0, nullptr);

        VkBuffer vertexBuffer[] = {this->vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(this->commandBuffers[i], 0, 1, vertexBuffer, offsets);
        vkCmdBindIndexBuffer(this->commandBuffers[i], this->indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        //vkCmdDraw(this->commandBuffers[i], 3, 1, 0, 0);
        vkCmdDrawIndexed(this->commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffers[i]);

        if (VK_SUCCESS != vkEndCommandBuffer(this->commandBuffers[i]))
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

void HelloTriangleApplication::createOrchestratorObjects()
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

void HelloTriangleApplication::createVertexBuffer()
{
    size_t size = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(this->device,
                 this->physicalDevice,
                 size,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void *data;
    vkMapMemory(this->device, stagingBufferMemory, 0, size, 0, &data);
    memcpy(data, vertices.data(), size);
    vkUnmapMemory(this->device, stagingBufferMemory);

    createBuffer(this->device,
                 this->physicalDevice,
                 size,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 this->vertexBuffer,
                 this->vertexBufferMemory);

    copyBuffer(this->device,
               this->commandPool,
               this->graphicQueue,
               stagingBuffer,
               this->vertexBuffer,
               size);

    vkDestroyBuffer(this->device, stagingBuffer, nullptr);
    vkFreeMemory(this->device, stagingBufferMemory, nullptr);
}

void HelloTriangleApplication::createIndexBuffer()
{
    size_t size = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(this->device,
                 this->physicalDevice,
                 size,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void *data;
    vkMapMemory(this->device, stagingBufferMemory, 0, size, 0, &data);
    memcpy(data, indices.data(), size);
    vkUnmapMemory(this->device, stagingBufferMemory);

    createBuffer(this->device,
                 this->physicalDevice,
                 size,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 this->indexBuffer,
                 this->indexBufferMemory);

    copyBuffer(this->device,
               this->commandPool,
               this->graphicQueue,
               stagingBuffer,
               this->indexBuffer,
               size);

    vkDestroyBuffer(this->device, stagingBuffer, nullptr);
    vkFreeMemory(this->device, stagingBufferMemory, nullptr);
}

void HelloTriangleApplication::createDescriptorSetLayout()
{
    VkDescriptorSetLayoutBinding uboLayoutBinding = {};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.pImmutableSamplers = nullptr;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};

    VkDescriptorSetLayoutCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    createInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    createInfo.pBindings = bindings.data();

    if (VK_SUCCESS != vkCreateDescriptorSetLayout(this->device, &createInfo, nullptr, &this->descriptorSetLayout))
    {
        throw std::runtime_error("failed to create a descriptor layout");
    }
}

void HelloTriangleApplication::createUboBuffer()
{
    createBuffer(this->device,
                 this->physicalDevice,
                 sizeof(UniformBufferObject),
                 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 this->uboBuffer,
                 this->uboBufferMemory);
}


void HelloTriangleApplication::updateUniformBuffer()
{
    static float time = .0000001f;
    time += 0.0001f;

    UniformBufferObject ubo = {};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f,
                                10.0f);
    ubo.proj[1][1] *= -1;

    void *data;

    size_t size = sizeof(UniformBufferObject);
    vkMapMemory(this->device,
                this->uboBufferMemory,
                0,
                size,
                0,
                &data);
    memcpy(data, &ubo, size);
    vkUnmapMemory(this->device, this->uboBufferMemory);
}

void HelloTriangleApplication::createDescriptorpool()
{
    std::array<VkDescriptorPoolSize, 2> poolSizes = {};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = 1;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = 1;

    VkDescriptorPoolCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    createInfo.pPoolSizes = poolSizes.data();
    createInfo.maxSets = 1;

    if (VK_SUCCESS != vkCreateDescriptorPool(this->device, &createInfo, nullptr, &this->descriptorPool))
    {
        throw std::runtime_error("failed to create descriptor pool");
    }
};

void HelloTriangleApplication::createDescriptorSet()
{
    VkDescriptorSetLayout layouts[] = {this->descriptorSetLayout};
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = this->descriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = layouts;

    if (VK_SUCCESS != vkAllocateDescriptorSets(this->device, &allocInfo, &this->descriptorSet))
    {
        throw std::runtime_error("failed to create descriptorSet");
    }

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = this->uboBuffer;
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkDescriptorImageInfo imageInfo = {};
    imageInfo.sampler = this->textureSampler;
    imageInfo.imageView = this->textureImageView;
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    std::array<VkWriteDescriptorSet, 2> writeDescriptors = {};
    writeDescriptors[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptors[0].dstSet = this->descriptorSet;
    writeDescriptors[0].dstBinding = 0;
    writeDescriptors[0].dstArrayElement = 0;
    writeDescriptors[0].descriptorCount = 1;
    writeDescriptors[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeDescriptors[0].pBufferInfo = &bufferInfo;

    writeDescriptors[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptors[1].dstSet = descriptorSet;
    writeDescriptors[1].dstBinding = 1;
    writeDescriptors[1].dstArrayElement = 0;
    writeDescriptors[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptors[1].descriptorCount = 1;
    writeDescriptors[1].pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(this->device,
                           static_cast<uint32_t>(writeDescriptors.size()),
                           writeDescriptors.data(),
                           0,
                           nullptr);
}

void HelloTriangleApplication::createTextureImage()
{
    int texWidth, texHeight, texChannels;
    stbi_uc *pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    VkDeviceSize imageSize = texWidth * texHeight * 4;

    if (!pixels)
    {
        throw std::runtime_error("failed to load texture image");
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(this->device,
                 this->physicalDevice,
                 imageSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void *data;
    vkMapMemory(this->device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<uint32_t>(imageSize));
    vkUnmapMemory(this->device, stagingBufferMemory);

    stbi_image_free(pixels);

    createImage(this->device,
                this->physicalDevice,
                texWidth,
                texWidth,
                VK_FORMAT_R8G8B8A8_UNORM,
                VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                this->textureImage,
                this->textureImageMemory);

    transitionImageLayout(this->device,
                          this->commandPool,
                          this->graphicQueue,
                          this->textureImage,
                          VK_FORMAT_R8G8B8A8_UNORM,
                          VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    copyBufferToImage(this->device,
                      this->commandPool,
                      this->graphicQueue,
                      stagingBuffer,
                      this->textureImage,
                      static_cast<uint32_t>(texWidth),
                      static_cast<uint32_t>(texHeight));

    transitionImageLayout(this->device,
                          this->commandPool,
                          this->graphicQueue,
                          this->textureImage,
                          VK_FORMAT_R8G8B8A8_UNORM,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(this->device, stagingBuffer, nullptr);
    vkFreeMemory(this->device, stagingBufferMemory, nullptr);
}

void HelloTriangleApplication::createTextureImageView()
{
    this->textureImageView = createImageView(this->textureImage,
                                             VK_FORMAT_R8G8B8A8_UNORM,
                                             VK_IMAGE_ASPECT_COLOR_BIT);
}

VkImageView HelloTriangleApplication::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
{
    VkImageViewCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = image;
    createInfo.format = format;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.subresourceRange.aspectMask = aspectFlags;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    if (VK_SUCCESS != vkCreateImageView(this->device, &createInfo, nullptr, &imageView))
    {
        throw std::runtime_error("failed to create texture image view");
    }

    return imageView;
}


void HelloTriangleApplication::createTextureSampler()
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;

    if (VK_SUCCESS != vkCreateSampler(this->device, &samplerInfo, nullptr, &this->textureSampler))
    {
        throw std::runtime_error("failed to create texture sampler");
    }
}

void HelloTriangleApplication::createDepthResources()
{
    VkFormat depthFormat = findDepthFormat(this->physicalDevice);

    createImage(this->device,
                this->physicalDevice,
                this->swapChainExtent.width,
                this->swapChainExtent.height,
                depthFormat,
                VK_IMAGE_TILING_OPTIMAL,
                VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                this->depthImage,
                this->depthImageMemory);

    this->depthImageView = createImageView(this->depthImage,
                                           depthFormat ,
                                           VK_IMAGE_ASPECT_DEPTH_BIT);
    transitionImageLayout(this->device,
                          this->commandPool,
                          this->graphicQueue,
                          this->depthImage,
                          depthFormat,
                          VK_IMAGE_LAYOUT_UNDEFINED,
                          VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void HelloTriangleApplication::loadModel()
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if( !tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str()) )
    {
        throw std::runtime_error(err);
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            VertexPosColorTex vertex = {};

            vertex.pos = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};

            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }
}