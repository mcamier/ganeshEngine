#include "VulkanContextManager.hpp"

#include <array>

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>

#include "../window/WindowManager.hpp"

namespace rep
{

void VulkanContextManager::vInit(VulkanContextManagerInitializeArgs_t args)
{
    initVulkanInstance(args);
    REP_DEBUG("  instance initialized", LogChannelBitsFlag::RENDER);

    createSurface(this->vulkanInstance,
                  WindowManager::get().getWindowHandle(),
                  &this->surface);
    REP_DEBUG("  surface initialized", LogChannelBitsFlag::RENDER);

    std::array<const char *, 1> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    pickPhysicalDevice(this->vulkanInstance,
                       this->surface,
                       static_cast<uint16_t>(deviceExtensions.size()),
                       deviceExtensions.data(),
                       &this->physicalDevice);
    REP_DEBUG("  physical device selected", LogChannelBitsFlag::RENDER);

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice, this->surface);

    createLogicalDevice(this->physicalDevice,
                        indices,
                        args.validationLayerCount,
                        args.ppValidationLayersCount,
                        static_cast<uint32_t>(deviceExtensions.size()),
                        deviceExtensions.data(),
                        &this->device);
    REP_DEBUG("  logical device initialized", LogChannelBitsFlag::RENDER);

    this->initAsyncObjects();
    REP_DEBUG("  async objects initialized", LogChannelBitsFlag::RENDER);

    vkGetDeviceQueue(this->device, indices.graphicsFamily, 0, &this->graphicQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily, 0, &this->presentQueue);

    this->initSwapchain();
    REP_DEBUG("  swapchain initialized", LogChannelBitsFlag::RENDER);

    createRenderPass(this->physicalDevice,
                     this->device,
                     this->swapchainImageFormat,
                     &this->renderPass);
    REP_DEBUG("  renderpass initialized", LogChannelBitsFlag::RENDER);

    createCommandPool(this->physicalDevice,
                      this->device,
                      indices.graphicsFamily,
                      &this->graphicCommandPool);
    REP_DEBUG("  command pool initialized", LogChannelBitsFlag::RENDER);

    /*
    this->initDepthTest();
    REP_DEBUG("  depth test initialized", LogChannelBitsFlag::RENDER);
*/

    REP_DEBUG("RenderManager initialized", LogChannelBitsFlag::RENDER)
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
    REP_DEBUG("RenderManager initialization...", LogChannelBitsFlag::RENDER)

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
    REP_DEBUG("  vulkan instance initialized", LogChannelBitsFlag::RENDER);

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
        REP_DEBUG("  debug callback initialized", LogChannelBitsFlag::RENDER);
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
    REP_DEBUG("Image amount detected for swapchain is : " << imageCount, LogChannelBitsFlag::RENDER)

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
    REP_DEBUG("create " << swapchainImageViews.size() << " image views for the swapchain", LogChannelBitsFlag::RENDER)
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
        REP_WARNING("  framebuffer is initialized", LogChannelBitsFlag::RENDER)
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
    REP_DEBUG("RenderManager destroyed", LogChannelBitsFlag::RENDER)
}


uint64_t memoryAlloc_t::lastId = 0;


void VulkanMemoryManager::vInit(VulkanMemoryManagerInitializeArgs_t args)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    VkBufferUsageFlags bufferUsageFlags = VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
                                          VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                          VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
                                          VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
                                          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                                          VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                          VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    REP_DEBUG("Vulkan memory pool : " << args.poolSize << " chunks, of " << args.chunkSize << " bytes each",
              LogChannelBitsFlag::DEFAULT)
    chunkSize = args.chunkSize;
    poolSize = args.poolSize;
    memoryPool.resize(args.poolSize);
    allocations.resize(args.poolSize);
    for (int i = 0; i < args.poolSize; i++)
    {
        memoryPool[i].size = chunkSize;
        createBuffer(ctxt.device,
                     ctxt.physicalDevice,
                     args.chunkSize,
                     bufferUsageFlags,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     memoryPool[i].buffer,
                     memoryPool[i].memory);
        REP_DEBUG("  chunk of " << args.chunkSize << " bytes allocated", LogChannelBitsFlag::DEFAULT)
    }
}

void VulkanMemoryManager::vDestroy()
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    // destroy all buffers allocated
    for (int chunk = 0; chunk < poolSize; chunk++)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr)
        {
            vkDestroyBuffer(ctxt.device, alloc->buffer, nullptr);
            alloc = alloc->pNext;
        }
    }

    // detroy the memory chunks
    for (int chunk = 0; chunk < poolSize; chunk++)
    {
        vkFreeMemory(ctxt.device, memoryPool[chunk].memory, nullptr);
        vkDestroyBuffer(ctxt.device, memoryPool[chunk].buffer, nullptr);
    }
    REP_DEBUG("VulkanMemoryManager destroyed", LogChannelBitsFlag::DEFAULT)
}


memoryAllocId VulkanMemoryManager::allocateBuffer(uint64_t size, VkBufferUsageFlags usage)
{
    return this->allocateWithPolicy<BufferAllocatorPolicy>(size, usage);
}


memoryAllocId VulkanMemoryManager::allocateUniform(uint64_t size)
{
    return this->allocateWithPolicy<UniformAllocatorPolicy>(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
}

memoryAllocId VulkanMemoryManager::findAvailableMemory(VkDeviceSize size, VkDeviceSize alignment, VkBuffer &buffer)
{
    // TODO loop on every chunk
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    memoryAllocId allocId = -1;
    uint8_t chunkIndex = 0;
    bool memoryLocationFound = false;

    memoryAlloc_t *newAlloc = new memoryAlloc_t();
    newAlloc->memoryChunkIndex = chunkIndex;
    newAlloc->memoryChunkOffset = 0;
    newAlloc->alignmentOffset = 0;
    newAlloc->allocationSize = size;
    newAlloc->buffer = buffer;

    memoryAlloc_t *current_alloc = allocations[chunkIndex];

    // No allocation already exists in this chunk
    if (current_alloc == nullptr)
    {
        allocations[chunkIndex] = newAlloc;

        vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory, 0);
        memoryLocationFound = true;
        allocId = allocations[chunkIndex]->id;
    }

    // Look up for enough room to allocate new memory block
    while (current_alloc != nullptr && !memoryLocationFound)
    {
        // compute the position of the end of the current memory block
        uint64_t position = current_alloc->getEndPosition();
        newAlloc->alignmentOffset = alignment - (position % alignment);

        if (current_alloc->pNext != nullptr)
        {
            // we are not at the end of linked list, but we check if there is a gap with enough room to host the
            // requested memory block
            memoryAlloc_t *next_alloc = current_alloc->pNext;
            uint64_t gap = next_alloc->memoryChunkOffset - position;
            if (gap >= newAlloc->alignmentOffset + size)
            {
                // the allocation fits between two previously allocated block
                // insert a node between two nodes
                newAlloc->memoryChunkOffset = position;
                newAlloc->pPrevious = current_alloc;
                newAlloc->pNext = next_alloc;
                current_alloc->pNext = newAlloc;
                next_alloc->pPrevious = newAlloc;

                vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory,
                                   newAlloc->getAlignedBeginPosition());
                memoryLocationFound = true;
                allocId = newAlloc->id;
            }
        }
        else
        {
            // we are at the end of the linked list, we check if there is enough room for the request memory block
            uint64_t lastGap = memoryPool[chunkIndex].size - position;
            if (lastGap >= newAlloc->alignmentOffset + size)
            {
                // the allocation fits between two previously allocated block
                // insert a node between two nodes
                newAlloc->memoryChunkOffset = position;
                newAlloc->pPrevious = current_alloc;
                newAlloc->pNext = nullptr;
                current_alloc->pNext = newAlloc;

                vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory,
                                   newAlloc->getAlignedBeginPosition());
                memoryLocationFound = true;
                allocId = newAlloc->id;
            }
        }
        current_alloc = current_alloc->pNext;
    }

    if (!memoryLocationFound)
    {
        delete newAlloc;
        throw std::runtime_error("Unable to find enough room to sub allocate memory");
    }
    return allocId;
}


void VulkanMemoryManager::free(memoryAllocId allocId)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    bool found = false;
    int chunk = 0;

    while (chunk < poolSize && !found)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && !found)
        {
            if (alloc->id == allocId)
            {
                found = true;
                vkDestroyBuffer(ctxt.device, alloc->buffer, nullptr);
                alloc->pPrevious->pNext = alloc->pNext;
                delete alloc;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }
}


void VulkanMemoryManager::dump()
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    REP_DEBUG("##################################", LogChannelBitsFlag::DEFAULT)
    REP_DEBUG("DUMP MEMORY CHUNK 0", LogChannelBitsFlag::DEFAULT)
    memoryAlloc_t *alloc = allocations[0];
    while (alloc != nullptr)
    {
        uint64_t position = alloc->memoryChunkOffset + alloc->allocationSize;
        REP_DEBUG("[" << alloc->memoryChunkOffset << "] " << alloc->allocationSize << " bytes allocated (#" << alloc->id
                      << ")",
                  LogChannelBitsFlag::DEFAULT)
        if (alloc->pNext != nullptr)
        {
            memoryAlloc_t *next_alloc = alloc->pNext;
            uint64_t gap = next_alloc->memoryChunkOffset - position;
            if (gap != 0)
            {
                REP_DEBUG("[" << alloc->memoryChunkOffset + alloc->allocationSize << "] " << gap << " bytes free",
                          LogChannelBitsFlag::DEFAULT)
            }
        }
        else
        {
            uint64_t lastGap = memoryPool[0].size - position;
            REP_DEBUG("[" << alloc->memoryChunkOffset + alloc->allocationSize << "] " << lastGap << " bytes free",
                      LogChannelBitsFlag::DEFAULT)
        }
        alloc = alloc->pNext;
    }
    REP_DEBUG("DUMP MEMORY CHUNK 0", LogChannelBitsFlag::DEFAULT)
    REP_DEBUG("##################################", LogChannelBitsFlag::DEFAULT)
}

VkBuffer VulkanMemoryManager::getBuffer(memoryAllocId allocId)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    int chunk = 0;
    VkBuffer buffer = VK_NULL_HANDLE;

    while (chunk < poolSize && buffer == VK_NULL_HANDLE)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && buffer == VK_NULL_HANDLE)
        {
            if (alloc->id == allocId)
            {
                buffer = alloc->buffer;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }

    if (buffer == VK_NULL_HANDLE)
    {
        throw std::runtime_error("unable to find memory with id " + allocId);
    }
    return buffer;
}


void
VulkanMemoryManager::getMemoryAllocation(memoryAllocId allocId, memoryAlloc_t **memoryAlloc, VkDeviceMemory *memory)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    bool found = false;
    int chunk = 0;

    while (chunk < poolSize && !found)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && !found)
        {
            if (alloc->id == allocId)
            {
                found = true;
                *memoryAlloc = alloc;
                *memory = memoryPool[chunk].memory;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }

    if (!found)
    {
        throw std::runtime_error("unable to find memory with id " + allocId);
    }
}


VkDeviceSize UniformAllocatorPolicy::getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    return deviceProperties.limits.minUniformBufferOffsetAlignment;
}


VkDeviceSize UniformAllocatorPolicy::createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage)
{
    VkBuffer buffer;
    // we create a specific buffer for the new "sub-allocation"
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (VK_SUCCESS != vkCreateBuffer(device, &bufferInfo, nullptr, &buffer))
    {
        throw std::runtime_error("[UniformAllocatorPolicy::createBuffer] failed to create vertex buffer");
    }
    return buffer;
}

VkDeviceSize BufferAllocatorPolicy::getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer)
{
    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
    return memoryRequirements.alignment;
}

VkDeviceSize BufferAllocatorPolicy::createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage)
{
    VkBuffer buffer;
    // we create a specific buffer for the new "sub-allocation"
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (VK_SUCCESS != vkCreateBuffer(device, &bufferInfo, nullptr, &buffer))
    {
        throw std::runtime_error("[BufferAllocatorPolicy::createBuffer] failed to create vertex buffer");
    }
    return buffer;
}

}