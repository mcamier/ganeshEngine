#include "RenderManager.hpp"

#include "../window/WindowManager.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <array>
#include <vector>
#include <string>

namespace rep
{

void loadModel(std::string &modelPath,
               std::vector<VertexPosColorTex> & vertices,
               std::vector<uint32_t > & indices)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath.c_str()))
    {
        throw std::runtime_error(err);
    }

    for (const auto &shape : shapes)
    {
        for (const auto &index : shape.mesh.indices)
        {
            VertexPosColorTex vertex = {};

            vertex.position = {
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

void RenderManager::vInit(RenderManagerInitializeArgs_t args)
{
    /**
     * Temp load mesh
     * TODO remove it
     */
    std::string path("C:/Users/Mickael/Documents/workspace/renderEnginePlayground/models/cube.obj");
    loadModel(path, this->vertices, this->indices);
    meshInstance_t meshInstance = {};
    meshInstance.indexSize = sizeof(uint32_t);
    meshInstance.indexCount = this->indices.size();
    meshInstance.indices = this->indices.data();
    meshInstance.vertexSize = sizeof(VertexPosColorTex);
    meshInstance.verticeCount= this->indices.size();
    meshInstance.vertices = this->vertices.data();
    this->registeredMeshes.push_back(meshInstance);


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
    REP_DEBUG("  vulkan instance initialized", LOG_CHANNEL::RENDER);
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
    REP_DEBUG("  debug callback initialized", LOG_CHANNEL::RENDER);

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
    REP_DEBUG("  debug callback choosed", LOG_CHANNEL::RENDER);

    QueueFamilyIndices indices = findQueueFamilies(this->physicalDevice, this->surface);

    createLogicalDevice(this->physicalDevice,
                        indices,
                        args.validationLayerCount,
                        args.ppValidationLayersCount,
                        static_cast<uint32_t>(deviceExtensions.size()),
                        deviceExtensions.data(),
                        &this->device);
    REP_DEBUG("  logical device initialized", LOG_CHANNEL::RENDER);

    this->createAsyncObjects();
    REP_DEBUG("  async objects initialized", LOG_CHANNEL::RENDER);

    vkGetDeviceQueue(this->device, indices.graphicsFamily, 0, &this->graphicQueue);
    vkGetDeviceQueue(this->device, indices.presentFamily, 0, &this->presentQueue);

    this->createSwapchain();
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

    createDepthTest();
    REP_DEBUG("  depth test initialized", LOG_CHANNEL::RENDER);

    createDescriptorPool(this->device,
                         &this->descriptorPool);
    REP_DEBUG("  descriptor pool initialized", LOG_CHANNEL::RENDER);

    /**
     * Setup a first default pipeline
     */
    REP_DEBUG("  default graphic pipeline initialization...", LOG_CHANNEL::RENDER);
    this->createDefaultGraphicPipeline(DEFAULT_VERT_SHADER_LOCATION, DEFAULT_FRAG_SHADER_LOCATION);
    REP_DEBUG("  default graphic pipeline initialized", LOG_CHANNEL::RENDER);

    this->createFramebuffers();
    REP_DEBUG("  framebuffers initialized", LOG_CHANNEL::RENDER);

    this->createVertexAndIndexBuffer();
    REP_DEBUG("  vertex and index buffers initialized", LOG_CHANNEL::RENDER);

    this->createCommandBuffers();
    REP_DEBUG("  command buffers initialized", LOG_CHANNEL::RENDER);

    REP_DEBUG("RenderManager initialized", LOG_CHANNEL::RENDER)
}


void RenderManager::createSwapchain()
{
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

    vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, nullptr);
    this->swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(this->device, this->swapchain, &imageCount, this->swapchainImages.data());

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
}


void RenderManager::updateSwapchain()
{
    vkDeviceWaitIdle(this->device);

    this->destroySwapchain();

    this->createSwapchain();
    this->createDefaultGraphicPipeline(DEFAULT_VERT_SHADER_LOCATION, DEFAULT_FRAG_SHADER_LOCATION);
    this->createDepthTest();
    this->createFramebuffers();
    this->createCommandBuffers();
}


void RenderManager::destroySwapchain()
{
    /*vkDestroyImageView(device, this->depthImageView, nullptr);
    vkDestroyImage(device, this->depthImage, nullptr);
    vkFreeMemory(device, this->depthImageMemory, nullptr);
    */
    vkFreeCommandBuffers(this->device,
                         this->graphicCommandPool,
                         static_cast<uint32_t>(commandBuffers.size()),
                         commandBuffers.data());

    for (auto framebuffer : this->swapChainFramebuffers)
    {
        vkDestroyFramebuffer(device,
                             framebuffer,
                             nullptr);
    }

    this->destroyDepthTest();

    for (auto &p : this->availablePipelines)
    {
        destroyPipeline(this->device, p);
    }

    vkDestroyRenderPass(this->device,
                        this->renderPass,
                        nullptr);

    for (auto &imageView : this->swapchainImageViews)
    {
        vkDestroyImageView(this->device,
                           imageView,
                           nullptr);
    }
    vkDestroySwapchainKHR(this->device,
                          this->swapchain,
                          nullptr);
}

void RenderManager::createDefaultGraphicPipeline(const char *vertShaderFilename,
                                                 const char *fragShaderFilename)
{
    this->availablePipelines.resize(1);
    pipelineInfos_t pipelineInfos = pipelineInfosBuilder<VertexPosColorTex>::build();
    createGraphicPipeline(this->device,
                          this->descriptorPool,
                          this->renderPass,
                          this->swapchainExtent,
                          vertShaderFilename,
                          fragShaderFilename,
                          &pipelineInfos);
    if (pipelineInfos.pipeline == VK_NULL_HANDLE)
    {
        REP_FATAL("Failed to create default pipeline", LOG_CHANNEL::RENDER);
    }
    this->availablePipelines[0] = pipelineInfos;

}


void RenderManager::createDepthTest()
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

void RenderManager::destroyDepthTest()
{
    vkFreeMemory(this->device, this->depthImageMemory, nullptr);
    vkDestroyImageView(this->device, this->depthImageView, nullptr);
    vkDestroyImage(this->device, this->depthImage, nullptr);
}


void RenderManager::createFramebuffers()
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


void RenderManager::createVertexAndIndexBuffer()
{
    /**
     * get total size of the buffer
     */
    uint64_t bufferSize = 0;
    for (meshInstance_t &mesh : this->registeredMeshes)
    {
        bufferSize += mesh.verticeCount * mesh.vertexSize;
        bufferSize += mesh.indexCount * mesh.indexSize;
    }

    if (bufferSize == 0)
        return;

    /**
     * instantiate buffer and allocate memory for staging
     */
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(this->device,
                 this->physicalDevice,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    createBuffer(this->device,
                 this->physicalDevice,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 this->vertexAndIndexBuffer,
                 this->vertexAndIndexBufferMemory);

    uint32_t meshOffset = 0;
    uint32_t meshIndexesOffset = 0;
    uint32_t indicesSize = 0;
    for (meshInstance_t &mesh : this->registeredMeshes)
    {
        meshIndexesOffset = mesh.verticeCount * mesh.vertexSize;
        indicesSize = mesh.indexCount * mesh.indexSize;

        /**
         * persist buffer's offset for later use during drawing process
         */
        mesh.offset = {meshOffset, meshIndexesOffset};

        // populate with vertices
        populateDeviceMemory(this->device,
                             stagingBufferMemory,
                             meshOffset,
                             meshIndexesOffset,
                             mesh.vertices);
        // populate with indices
        populateDeviceMemory(this->device,
                             stagingBufferMemory,
                             meshOffset + meshIndexesOffset,
                             indicesSize,
                             mesh.indices);

        // after meshOffset assigment, its value is the offset of the next mesh
        meshOffset += meshIndexesOffset + indicesSize;
    }


    /**
     * copy staging buffer content into fast memory in GPU
     */
    copyBuffer(this->device,
               this->graphicCommandPool,
               this->graphicQueue,
               stagingBuffer,
               this->vertexAndIndexBuffer,
               bufferSize);

    /**
     * destroy buffer and free memory for staging buffer
     */
    vkDestroyBuffer(this->device, stagingBuffer, nullptr);
    vkFreeMemory(this->device, stagingBufferMemory, nullptr);
}


void RenderManager::createCommandBuffers()
{
    this->commandBuffers.resize(this->swapChainFramebuffers.size());

    std::array<VkClearValue, 2> clearValues = {};
    clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};

    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = this->graphicCommandPool;
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
        renderPassInfo.renderArea.extent = this->swapchainExtent;
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(this->commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        /**
         *  for now let's assume all meshes use the same default pipeline
         */
        pipelineInfos_t &pipeline = this->availablePipelines[0];
        vkCmdBindPipeline(this->commandBuffers[i],
                          VK_PIPELINE_BIND_POINT_GRAPHICS,
                          pipeline.pipeline);

        vkCmdBindDescriptorSets(commandBuffers[i],
                                VK_PIPELINE_BIND_POINT_GRAPHICS,
                                pipeline.pipelineLayout,
                                0,
                                1,
                                &descriptorSet,
                                0,
                                nullptr);

        for (meshInstance_t &meshInstance : this->registeredMeshes)
        {
            vkCmdBindVertexBuffers(this->commandBuffers[i],
                                   0,
                                   1,
                                   &this->vertexAndIndexBuffer,
                                   &meshInstance.offset.meshOffset);

            vkCmdBindIndexBuffer(this->commandBuffers[i],
                                 this->vertexAndIndexBuffer,
                                 meshInstance.offset.meshOffset + meshInstance.offset.meshRelativeIndicesOffset,
                                 VK_INDEX_TYPE_UINT32);

            vkCmdDrawIndexed(this->commandBuffers[i],
                             static_cast<uint32_t>(meshInstance.indexSize),
                             1, 0, 0, 0);
        }

        vkCmdEndRenderPass(commandBuffers[i]);

        if (VK_SUCCESS != vkEndCommandBuffer(this->commandBuffers[i]))
        {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}


void RenderManager::vUpdate()
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
        this->updateSwapchain();
        return;
    }
    else if (VK_SUCCESS != result && VK_SUBOPTIMAL_KHR != result)
    {
        throw std::runtime_error("failed to acquire swap chain image");
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

    result = vkQueuePresentKHR(this->presentQueue, &presentInfo);

    if (VK_ERROR_OUT_OF_DATE_KHR == result || VK_SUBOPTIMAL_KHR == result)
    {
        updateSwapchain();
    }
    else if (VK_SUCCESS != result)
    {
        throw std::runtime_error("failed to present swapchain image");
    }

    currentFrame = (currentFrame + 1) % MAX_CONCURRENT_FRAMES;
}


void RenderManager::createAsyncObjects()
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

void RenderManager::destroyAsyncObjects()
{
    for (int i = 0; i < MAX_CONCURRENT_FRAMES; i++)
    {
        vkDestroySemaphore(this->device, this->imageAvailableSemaphores[i], nullptr);
        vkDestroySemaphore(this->device, this->renderFinishedSemaphores[i], nullptr);
        vkDestroyFence(this->device, this->inFligtFences[i], nullptr);
    }
}

void RenderManager::vDestroy()
{

    vkFreeMemory(this->device, vertexAndIndexBufferMemory, nullptr);
    vkDestroyBuffer(this->device, this->vertexAndIndexBuffer, nullptr);
    destroySwapchain();
    vkDestroyDescriptorPool(this->device, this->descriptorPool, nullptr);
    vkDestroyCommandPool(this->device, this->graphicCommandPool, nullptr);
    this->destroyAsyncObjects();
    vkDestroyDevice(this->device, nullptr);
    destroyDebugReportCallbackEXT(this->vulkanInstance, this->debugReportCallback, nullptr);
    vkDestroyInstance(this->vulkanInstance, nullptr);
    REP_DEBUG("RenderManager destroyed", LOG_CHANNEL::RENDER)
}

}