#define GLFW_INCLUDE_VULKAN

#include <set>
#include <array>

#include <GLFW/glfw3.h>
#include <tiny_obj_loader.h>

#include "helper.hpp"

using ge::utils::LogChannelBitsFlag;

namespace ge {
namespace vulkan {
namespace helper {

template<>
void loadModel<VertexPosNormalColorTex>(std::string &modelPath,
                                        std::vector<VertexPosNormalColorTex> &vertices,
                                        std::vector<uint32_t> &indices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath.c_str())) {
        throw std::runtime_error(err);
    }

    for (const auto &shape : shapes) {
        for (const auto &index : shape.mesh.indices) {
            VertexPosNormalColorTex vertex = {};

            vertex.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2],
            };

            /*vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
            };*/

            vertex.color = {1.0f, 0.5f, 0.0f};
/*
            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };*/

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    REP_DEBUG("mesh loaded [" << vertices.size() << " vertices] [" << indices.size() << " indices]",
              LogChannelBitsFlag::RENDER)
}


std::vector<const char *> getRequiredExtensions() {
    std::vector<const char *> extensions;
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        extensions.push_back(glfwExtensions[i]);
    }

    extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    //#ifdef _DEBUG
    //    extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    //#endif


    return extensions;
}


bool isValidationLayerSupported(uint16_t validationLayerCount,
                                const char **ppValidationLayers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (int i = 0; i < validationLayerCount; i++) {
        const char *layerName = ppValidationLayers[i];
        bool layerFound = false;

        for (const VkLayerProperties &layerProp : availableLayers) {
            if (strcmp(layerName, layerProp.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}


void createSurface(VkInstance &vulkanInstance,
                   GLFWwindow *window,
                   VkSurfaceKHR *surface) {
    VkResult result = glfwCreateWindowSurface(vulkanInstance, window, nullptr, surface);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}


void pickPhysicalDevice(VkInstance const &vulkanInstance,
                        VkSurfaceKHR surface,
                        uint16_t countRequiredExtension,
                        const char **ppDeviceExtensions,
                        VkPhysicalDevice *physicalDevice) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, devices.data());

    for (const VkPhysicalDevice &device : devices) {
        if (isPhysicalDeviceSuitable(device, surface, countRequiredExtension, ppDeviceExtensions)) {
            *physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}


bool isPhysicalDeviceSuitable(VkPhysicalDevice device,
                              VkSurfaceKHR surface,
                              uint16_t countRequiredExtension,
                              const char **ppDeviceExtensions) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices queueIndices = findQueueFamilies(device, surface);
    bool extensionsSupported = checkDeviceExtensionSupport(device, countRequiredExtension, ppDeviceExtensions);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainDetails = querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainDetails.formats.empty() && !swapChainDetails.presentModes.empty();
    }

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader &&
           queueIndices.isComplete() &&
           extensionsSupported &&
           swapChainAdequate &&
           deviceFeatures.samplerAnisotropy;
}


bool checkDeviceExtensionSupport(VkPhysicalDevice device,
                                 uint16_t requiredExtensionCount,
                                 const char **ppRequiredExtensions) {
    uint32_t extensionsCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionsCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCount, availableExtensions.data());

    for (int i = 0; i < requiredExtensionCount; i++) {
        const char *requiredExt = ppRequiredExtensions[i];
        bool extFound = false;

        for (const VkExtensionProperties &extension : availableExtensions) {
            if (strcmp(requiredExt, extension.extensionName) == 0) {
                extFound = true;
                break;
            }
        }

        if (!extFound) {
            return false;
        }
    }

    return true;
}


QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const VkQueueFamilyProperties &queueFamily : queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (queueFamily.queueCount > 0 && presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }
        i++;
    }

    return indices;
}


SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,
                                              VkSurfaceKHR surface) {
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    if (formatCount > 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
    if (presentModeCount > 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }
    return details;
}


void createLogicalDevice(VkPhysicalDevice physicalDevice,
                         QueueFamilyIndices indices,
                         uint32_t validationLayerCount,
                         const char **validationLayers,
                         uint32_t deviceExtensionCount,
                         const char **deviceExtensions,
                         VkDevice *device) {
    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceFeatures.samplerAnisotropy = VK_TRUE;
    deviceFeatures.fillModeNonSolid = VK_TRUE;
    deviceFeatures.wideLines = VK_TRUE;
    deviceFeatures.geometryShader = VK_TRUE;

    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.presentFamily, indices.graphicsFamily};

    for (int queueFamily : uniqueQueueFamilies) {
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
    createInfo.enabledExtensionCount = deviceExtensionCount;
    createInfo.ppEnabledExtensionNames = deviceExtensions;


#ifdef _DEBUG
    createInfo.enabledLayerCount = validationLayerCount;
    createInfo.ppEnabledLayerNames = validationLayers;
#else
    createInfo.enabledLayerCount = 0;
#endif

    if (VK_SUCCESS != vkCreateDevice(physicalDevice, &createInfo, nullptr, device)) {
        throw std::runtime_error("logical device creation failed");
    }
}


void createCommandPool(VkPhysicalDevice physicalDevice,
                       VkDevice device,
                       uint32_t queueIndex,
                       VkCommandPool *commandPool) {
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueIndex;
    poolInfo.flags = 0;

    if (VK_SUCCESS != vkCreateCommandPool(device, &poolInfo, nullptr, commandPool)) {
        throw std::runtime_error("failed to create command pool!");
    }
}


void createDescriptorPool(VkDevice device,
                          VkDescriptorPool *descriptorPool) {
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

    if (VK_SUCCESS != vkCreateDescriptorPool(device, &createInfo, nullptr, descriptorPool)) {
        throw std::runtime_error("failed to create descriptor pool");
    }
};


VkFormat findSupportedFormat(VkPhysicalDevice physicalDevice,
                             const std::vector<VkFormat> &candidates,
                             VkImageTiling tiling, VkFormatFeatureFlags features) {
    for (auto candidate : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, candidate, &props);
        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return candidate;
        } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return candidate;
        }
    }
    throw std::runtime_error("failed to find a supported format");
}


VkFormat findDepthFormat(VkPhysicalDevice physicalDevice) {
    return findSupportedFormat(physicalDevice,
                               {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
                               VK_IMAGE_TILING_OPTIMAL,
                               VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}


bool hasStencilComponent(VkFormat format) {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}


uint32_t findMemoryType(VkPhysicalDevice physicalDevice,
                        uint32_t typeFilter,
                        VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type");
}


void createBuffer(VkDevice device,
                  VkPhysicalDevice physicalDevice,
                  VkDeviceSize size,
                  VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties,
                  VkBuffer &buffer,
                  VkDeviceMemory &bufferMemory) {
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (VK_SUCCESS != vkCreateBuffer(device, &bufferInfo, nullptr, &buffer)) {
        throw std::runtime_error("failed to create vertex buffer");
    }

    VkMemoryRequirements memRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

    if (VK_SUCCESS != vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory)) {
        throw std::runtime_error("failed to allocate vertex buffer memory");
    }

    vkBindBufferMemory(device, buffer, bufferMemory, 0);

}


VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }

    for (const auto &availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}


VkPresentModeKHR chooseSwapPresentationMode(const std::vector<VkPresentModeKHR> &availableModes) {
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

    for (const VkPresentModeKHR &availableMode : availableModes) {
        if (availableMode == VK_PRESENT_MODE_MAILBOX_KHR ||
            availableMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availableMode;
        }
    }
    return bestMode;
}


VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                            uint32_t defaultWidth,
                            uint32_t defaultHeight) {
    /*
     * Vulkan tells us to match the resolution of the window by setting the width and height in the currentExtent
     * member. However, some window managers do allow us to differ here and this is indicated by setting the width
     * and height in currentExtent to a special value: the maximum value of uint32_t
     */
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {defaultWidth, defaultHeight};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}


void createImage(VkDevice device,
                 VkPhysicalDevice physicalDevice,
                 uint32_t width,
                 uint32_t height,
                 VkFormat format,
                 VkImageTiling tiling,
                 VkImageUsageFlags usage,
                 VkImage &textureImage,
                 VkDeviceMemory &textureImageMemory) {
    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = usage;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

    if (VK_SUCCESS != vkCreateImage(device, &imageInfo, nullptr, &textureImage)) {
        throw std::runtime_error("faild to create image");
    }

    VkMemoryRequirements imageMemRequirements = {};
    vkGetImageMemoryRequirements(device, textureImage, &imageMemRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice,
                                               imageMemRequirements.memoryTypeBits,
                                               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    allocInfo.allocationSize = imageMemRequirements.size;

    if (VK_SUCCESS != vkAllocateMemory(device, &allocInfo, nullptr, &textureImageMemory)) {
        throw std::runtime_error("failed to alloc memory for image");
    }

    vkBindImageMemory(device, textureImage, textureImageMemory, 0);
}


VkImageView createImageView(VkDevice device,
                            VkImage image,
                            VkFormat format,
                            VkImageAspectFlags aspectFlags) {
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
    if (VK_SUCCESS != vkCreateImageView(device, &createInfo, nullptr, &imageView)) {
        throw std::runtime_error("failed to create texture image view");
    }

    return imageView;
}


void createRenderPass(VkPhysicalDevice physicalDevice,
                      VkDevice device,
                      VkFormat swapchainImageFormat,
                      VkRenderPass *renderPass) {
    /*VkAttachmentDescription depthAttachment = {};
    depthAttachment.format = findDepthFormat(physicalDevice);
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;*/

    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = swapchainImageFormat;
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

    /*VkAttachmentReference depthAttachmentRef = {};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;*/

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    //subpass.pDepthStencilAttachment = &depthAttachmentRef;

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    //std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
    std::array<VkAttachmentDescription, 1> attachments = {colorAttachment};

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}


void createShaderModule(VkDevice device,
                        const std::vector<char> &code,
                        VkShaderModule *shaderModule) {
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

    if (VK_SUCCESS != vkCreateShaderModule(device, &createInfo, nullptr, shaderModule)) {
        throw std::runtime_error("failed to create shader module");
    }
}


VkCommandBuffer beginSingleTimeCommand(VkDevice device,
                                       VkCommandPool commandPool) {
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    if (VK_SUCCESS != vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer)) {
        throw std::runtime_error("failed to create single time command buffer");
    }

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}


void endSingleTimeCommand(VkDevice device,
                          VkCommandPool commandPool,
                          VkCommandBuffer commandBuffer,
                          VkQueue queueToSubmit) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;


    vkQueueSubmit(queueToSubmit, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(queueToSubmit);
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}


void transitionImageLayout(VkDevice device,
                           VkCommandPool commandPool,
                           VkQueue queue,
                           VkImage image,
                           VkFormat format,
                           VkImageLayout oldLayout,
                           VkImageLayout newLayout) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommand(device, commandPool);

    VkImageMemoryBarrier barrier = {};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;

    if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

        if (hasStencilComponent(format)) {
            barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }
    } else {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;

    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL &&
               newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED &&
               newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask =
                VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    } else {
        throw std::invalid_argument("unsupported layout transition!");
    }

    vkCmdPipelineBarrier(commandBuffer,
                         sourceStage, destinationStage,
                         0,
                         0, nullptr,
                         0, nullptr,
                         1, &barrier);

    endSingleTimeCommand(device, commandPool, commandBuffer, queue);
}


void populateDeviceMemory(VkDevice device,
                          VkDeviceMemory deviceMemory,
                          uint32_t offset,
                          uint32_t size,
                          void *pSrc) {

    void *data;
    vkMapMemory(device, deviceMemory, offset, size, 0, &data);
    memcpy(data, pSrc, size);
    vkUnmapMemory(device, deviceMemory);
}


void copyBuffer(VkDevice device,
                VkCommandPool commandPool,
                VkQueue queueToSubmit,
                VkBuffer sourceBuffer,
                VkBuffer destinationBuffer,
                uint64_t size) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommand(device, commandPool);

    VkBufferCopy copyInfo = {};
    copyInfo.size = size;
    vkCmdCopyBuffer(commandBuffer, sourceBuffer, destinationBuffer, 1, &copyInfo);

    endSingleTimeCommand(device, commandPool, commandBuffer, queueToSubmit);
}


VkResult createDebugReportCallbackEXT(VkInstance instance,
                                      const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugReportCallbackEXT *pCallback) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                           "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}


void destroyDebugReportCallbackEXT(VkInstance instance,
                                   VkDebugReportCallbackEXT callback,
                                   const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                            "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    } else {
        throw std::runtime_error("cannot get vkDestroyDebugReportCallbackEXT from vulkan instance");
    }
}

}
}
}