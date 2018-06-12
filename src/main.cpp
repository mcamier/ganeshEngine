#include <iostream>
#include <functional>
#include <array>

#include "Application.hpp"
#include "render/pipeline.hpp"

#include <tiny_obj_loader.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/matrix_transform.hpp>

using namespace rep;


inline float clamp(float x, float a, float b)
{
    return x < a ? x : b;
}


void loadModel(std::string &modelPath,
               std::vector<VertexPosNormalColorTex> &vertices,
               std::vector<uint32_t> &indices)
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

            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 0.5f, 0.0f};

            vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    REP_DEBUG("mesh loaded [" << vertices.size() << " vertices] [" << indices.size() << " indices]",
              LOG_CHANNEL::RENDER)
}


class Demo :
        public Application
{
private:
    std::string mesh = "C:/Users/Mickael/Documents/workspace/renderEnginePlayground/models/cube.obj";
    std::vector<VertexPosNormalColorTex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory bufferMemory = VK_NULL_HANDLE;

    VkBuffer uboBuffer = VK_NULL_HANDLE;
    VkDeviceMemory uboBufferMemory = VK_NULL_HANDLE;
    VkDeviceSize uboOffset;

    VkCommandBuffer drawCommands;
    Pipeline defaultPipeline;
    Pipeline normalVisualizerPipeline;

    VkSemaphore imageAcquiredSemaphore;
    VkSemaphore renderReadySemaphore;
    VkFence drawFinishedFence;

    VkClearColorValue clearColorValue = {0.0f, 0.0f, 0.0f, 0.0f};

protected:

    void initSyncObjects()
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

        VkSemaphoreCreateInfo imageAcquiredSemaphoreInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        VkResult result = vkCreateSemaphore(ctxt.device, &imageAcquiredSemaphoreInfo, nullptr,
                                            &this->imageAcquiredSemaphore);
        assert(result == VK_SUCCESS);

        VkSemaphoreCreateInfo renderFinishedSemaphoreInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        result = vkCreateSemaphore(ctxt.device, &renderFinishedSemaphoreInfo, nullptr, &this->renderReadySemaphore);
        assert(result == VK_SUCCESS);

        /*VkFenceCreateInfo drawFinishedFenceInfo = {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
        result = vkCreateFence(ctxt.device, &drawFinishedFenceInfo, nullptr, &this->drawFinishedFence);
        vkResetFences(ctxt.device, 1, &this->drawFinishedFence);
        assert(result == VK_SUCCESS);*/
    }

    void initUniformBuffer()
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        VkDeviceSize allocationSize;
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(ctxt.physicalDevice, &deviceProperties);
        VkDeviceSize minOffset = deviceProperties.limits.minUniformBufferOffsetAlignment;
        uint32_t sizeModel = sizeof(ModelTransformation);
        uint32_t sizeViewProj = sizeof(ViewProjTransformation);

        if (sizeModel < minOffset)
        {
            uboOffset = minOffset;
        }
        else
        {
            uboOffset = (uint64_t) ceil((double) sizeModel / (double) minOffset);
        }
        allocationSize = uboOffset + sizeof(ViewProjTransformation);

        createBuffer(ctxt.device,
                     ctxt.physicalDevice,
                     allocationSize,
                     VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                     this->uboBuffer,
                     this->uboBufferMemory);

        VkDescriptorBufferInfo modelBufferInfo = {};
        modelBufferInfo.buffer = this->uboBuffer;
        modelBufferInfo.offset = 0;
        modelBufferInfo.range = sizeof(ModelTransformation);

        VkDescriptorBufferInfo projViewBufferInfo = {};
        projViewBufferInfo.buffer = this->uboBuffer;
        projViewBufferInfo.offset = uboOffset;
        projViewBufferInfo.range = sizeof(ViewProjTransformation);

        VkDescriptorBufferInfo modelBufferInfo2 = {};
        modelBufferInfo2.buffer = this->uboBuffer;
        modelBufferInfo2.offset = 0;
        modelBufferInfo2.range = sizeof(ModelTransformation);

        VkDescriptorBufferInfo projViewBufferInfo2 = {};
        projViewBufferInfo2.buffer = this->uboBuffer;
        projViewBufferInfo2.offset = uboOffset;
        projViewBufferInfo2.range = sizeof(ViewProjTransformation);


        VkWriteDescriptorSet writeModelDescSet = {};
        writeModelDescSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeModelDescSet.dstSet = defaultPipeline.getDescriptorSet(0);
        writeModelDescSet.dstBinding = 0;
        writeModelDescSet.dstArrayElement = 0;
        writeModelDescSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writeModelDescSet.descriptorCount = 1;
        writeModelDescSet.pBufferInfo = &modelBufferInfo;

        VkWriteDescriptorSet writePojViewDescSet = {};
        writePojViewDescSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writePojViewDescSet.dstSet = defaultPipeline.getDescriptorSet(1);
        writePojViewDescSet.dstBinding = 0;
        writePojViewDescSet.dstArrayElement = 0;
        writePojViewDescSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writePojViewDescSet.descriptorCount = 1;
        writePojViewDescSet.pBufferInfo = &projViewBufferInfo;


        VkWriteDescriptorSet writeModelDescSet2 = {};
        writeModelDescSet2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeModelDescSet2.dstSet = normalVisualizerPipeline.getDescriptorSet(0);
        writeModelDescSet2.dstBinding = 0;
        writeModelDescSet2.dstArrayElement = 0;
        writeModelDescSet2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writeModelDescSet2.descriptorCount = 1;
        writeModelDescSet2.pBufferInfo = &modelBufferInfo2;

        VkWriteDescriptorSet writePojViewDescSet2 = {};
        writePojViewDescSet2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writePojViewDescSet2.dstSet = normalVisualizerPipeline.getDescriptorSet(1);
        writePojViewDescSet2.dstBinding = 0;
        writePojViewDescSet2.dstArrayElement = 0;
        writePojViewDescSet2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writePojViewDescSet2.descriptorCount = 1;
        writePojViewDescSet2.pBufferInfo = &projViewBufferInfo2;

        //VkWriteDescriptorSet writes[] = {writeModelDescSet, writePojViewDescSet};
        VkWriteDescriptorSet writes[] = {writeModelDescSet, writePojViewDescSet, writeModelDescSet2, writePojViewDescSet2};
        //vkUpdateDescriptorSets(ctxt.device, 2, writes, 0, nullptr);
        vkUpdateDescriptorSets(ctxt.device, 4, writes, 0, nullptr);
    }

    void updateUniformBuffer()
    {
        auto ctxt = VulkanContextManager::get().getContextInfos();
        auto extent = VulkanContextManager::get().getCurrentExtent();
        static float time = .0000001f;
        time += 0.0001f;

        ViewProjTransformation viewProj = {};
        viewProj.view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
        viewProj.proj = glm::perspective(glm::radians(45.0f), extent.width / (float) extent.height, 0.1f,
                                         10.0f);
        viewProj.proj[1][1] *= -1;

        ModelTransformation model = {};
        model.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        void *data;
        size_t size = sizeof(ModelTransformation);
        vkMapMemory(ctxt.device,
                    this->uboBufferMemory,
                    0,
                    size,
                    0,
                    &data);
        memcpy(data, &model, size);
        vkUnmapMemory(ctxt.device, this->uboBufferMemory);

        vkMapMemory(ctxt.device,
                    this->uboBufferMemory,
                    uboOffset,
                    sizeof(ViewProjTransformation),
                    0,
                    &data);
        memcpy(data, &viewProj, sizeof(ViewProjTransformation));
        vkUnmapMemory(ctxt.device, this->uboBufferMemory);
    }


    void vInit() override
    {
        initSyncObjects();
        loadModel(mesh, this->vertices, this->indices);
        loadModelIntoBuffer();
        initPipeline();
        initUniformBuffer();
        REP_DEBUG("application demo initialized", LOG_CHANNEL::DEFAULT)
    }

    void vUpdate() override
    {
        clearColorValue.float32[0] = clamp(clearColorValue.float32[0] + 0.00001f, 1.0f, 0.0f);
        clearColorValue.float32[1] = clamp(clearColorValue.float32[1] + 0.000001f, 1.0f, 0.0f);
        clearColorValue.float32[2] = clamp(clearColorValue.float32[2] + 0.00002f, 1.0f, 0.0f);
        clearColorValue.float32[3] = 1.0f;

        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        uint64_t timeout = std::numeric_limits<uint64_t>::max();
        uint32_t imageAcquired;
        //vkWaitForFences(ctxt.device, 1, &this->drawFinishedFence, VK_TRUE, timeout);
        //vkResetFences(ctxt.device, 1, &this->drawFinishedFence);

        VkResult result;
        VkFramebuffer framebuffer;
        updateUniformBuffer();

        /**
         * acquire a swapchain image
         */
        result = vkAcquireNextImageKHR(ctxt.device,
                                       ctxt.swapchain,
                                       timeout,
                                       this->imageAcquiredSemaphore,
                                       VK_NULL_HANDLE,
                                       &imageAcquired);
        assert(result == VK_SUCCESS);

        /**
         * create a framebuffer
         */
        VkImageView imageView = VulkanContextManager::get().getSwapchainImageView(imageAcquired);
        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = ctxt.renderPass;
        framebufferCreateInfo.width = VulkanContextManager::get().getCurrentExtent().width;
        framebufferCreateInfo.height = VulkanContextManager::get().getCurrentExtent().height;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &imageView;
        framebufferCreateInfo.layers = 1;
        result = vkCreateFramebuffer(ctxt.device, &framebufferCreateInfo, nullptr, &framebuffer);
        assert(result == VK_SUCCESS);

        /**
         * recording a commande buffer
         */
        recordDrawCommand(framebuffer);

        /**
         * submit command buffer
         */
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.pWaitSemaphores = &this->imageAcquiredSemaphore;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &this->drawCommands;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &this->renderReadySemaphore;

        if (VK_SUCCESS != vkQueueSubmit(ctxt.graphicQueue, 1, &submitInfo, VK_NULL_HANDLE))
        {
            throw std::runtime_error("failed to submit render commandbuffer for drawing");
        }

        /**
         * present image
         */
        VkSwapchainKHR swapChains[] = {ctxt.swapchain};

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &this->renderReadySemaphore;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageAcquired;

        result = vkQueuePresentKHR(ctxt.presentQueue, &presentInfo);
        assert(result == VK_SUCCESS);

        vkQueueWaitIdle(ctxt.graphicQueue);
        vkFreeCommandBuffers(ctxt.device, ctxt.graphicCommandPool, 1, &this->drawCommands);
        vkDestroyFramebuffer(ctxt.device, framebuffer, nullptr);
    }

    void vDestroy() override
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        vkDestroySemaphore(ctxt.device, this->imageAcquiredSemaphore, nullptr);
        vkDestroySemaphore(ctxt.device, this->renderReadySemaphore, nullptr);
        //vkDestroyFence(ctxt.device, this->drawFinishedFence, nullptr);
        this->defaultPipeline.release();
        this->normalVisualizerPipeline.release();
        vkFreeMemory(ctxt.device, this->bufferMemory, nullptr);
        vkDestroyBuffer(ctxt.device, this->buffer, nullptr);
        vkFreeMemory(ctxt.device, this->uboBufferMemory, nullptr);
        vkDestroyBuffer(ctxt.device, this->uboBuffer, nullptr);
        REP_DEBUG("application demo destroyed", LOG_CHANNEL::DEFAULT)
    }

    void recordDrawCommand(VkFramebuffer framebuffer)
    {
        VkResult result;
        std::array<VkClearValue, 2> clearValues;
        clearValues[0].color = clearColorValue;
        clearValues[1].depthStencil = {1.0f, 0};

        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        uint32_t offset = this->vertices.size() * sizeof(VertexPosNormalColorTex);

        VkCommandBufferAllocateInfo cmdBufAllocInfo = {};
        cmdBufAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmdBufAllocInfo.commandPool = ctxt.graphicCommandPool;
        cmdBufAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmdBufAllocInfo.commandBufferCount = 1;
        vkAllocateCommandBuffers(ctxt.device, &cmdBufAllocInfo, &this->drawCommands);

        VkRenderPassBeginInfo renderPassBeginInfo = {};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = ctxt.renderPass;
        renderPassBeginInfo.framebuffer = framebuffer;
        renderPassBeginInfo.renderArea.offset = {0, 0};
        renderPassBeginInfo.renderArea.extent = VulkanContextManager::get().getCurrentExtent();
        renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassBeginInfo.pClearValues = clearValues.data();

        VkCommandBufferBeginInfo cmdBufBeginInfo = {};
        cmdBufBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        result = vkBeginCommandBuffer(this->drawCommands, &cmdBufBeginInfo);
        assert(result == VK_SUCCESS);
        vkCmdBeginRenderPass(this->drawCommands, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        /**
         * draw regular model
         */
        vkCmdBindPipeline(this->drawCommands, VK_PIPELINE_BIND_POINT_GRAPHICS, defaultPipeline.getPipeline());

        vkCmdBindDescriptorSets(this->drawCommands,
                                VK_PIPELINE_BIND_POINT_GRAPHICS,
                                defaultPipeline.getPipelineLayout(),
                                0,
                                defaultPipeline.getDesciptorSetCount(),
                                defaultPipeline.getDescriptorSets(),
                                0,
                                nullptr);

        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(this->drawCommands, 0, 1, &this->buffer, offsets);
        vkCmdBindIndexBuffer(this->drawCommands, this->buffer, offset, VK_INDEX_TYPE_UINT32);

        vkCmdDrawIndexed(this->drawCommands, this->indices.size(), 1, 0, 0, 0);

        /**
         * draw model's normals
         */
        vkCmdBindPipeline(this->drawCommands, VK_PIPELINE_BIND_POINT_GRAPHICS, normalVisualizerPipeline.getPipeline());

        vkCmdBindDescriptorSets(this->drawCommands,
                                VK_PIPELINE_BIND_POINT_GRAPHICS,
                                normalVisualizerPipeline.getPipelineLayout(),
                                0,
                                normalVisualizerPipeline.getDesciptorSetCount(),
                                normalVisualizerPipeline.getDescriptorSets(),
                                0,
                                nullptr);

        vkCmdBindVertexBuffers(this->drawCommands, 0, 1, &this->buffer, offsets);
        vkCmdBindIndexBuffer(this->drawCommands, this->buffer, offset, VK_INDEX_TYPE_UINT32);

        vkCmdDrawIndexed(this->drawCommands, this->indices.size(), 1, 0, 0, 0);

        vkCmdEndRenderPass(this->drawCommands);
        result = vkEndCommandBuffer(this->drawCommands);
        assert(result == VK_SUCCESS);
    }

    void initPipeline()
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

        this->defaultPipeline = Pipeline::Builder()
                .setDevice(ctxt.device)
                .setRenderPass(ctxt.renderPass)
                .setViewport(ViewportStateCreateInfo(VulkanContextManager::get().getCurrentExtent()))
                .setVertexInputBinding(VertexInputInfo::from<VertexPosNormalColorTex>())
                .setVertexShader("../shaders/compiled/standard/vert.spv")
                .setFragmentShader("../shaders/compiled/standard/frag.spv")
                .addDescriptorSet(DescriptorSetLayoutInfo().addBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, 0, 1))
                .addDescriptorSet(DescriptorSetLayoutInfo().addBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, 0, 1))
                .build();

        this->normalVisualizerPipeline = Pipeline::Builder()
                .setDevice(ctxt.device)
                .setRenderPass(ctxt.renderPass)
                .setViewport(ViewportStateCreateInfo(VulkanContextManager::get().getCurrentExtent()))
                .setVertexShader("../shaders/compiled/normal_visualizer/vert.spv")
                .setGeometryShader("../shaders/compiled/normal_visualizer/geom.spv")
                .setFragmentShader("../shaders/compiled/normal_visualizer/frag.spv")
                .addDescriptorSet(
                        DescriptorSetLayoutInfo()
                                .addBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_GEOMETRY_BIT,
                                            0,
                                            1))
                .addDescriptorSet(
                        DescriptorSetLayoutInfo()
                                .addBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_GEOMETRY_BIT,
                                            0,
                                            1))
                .build();

    }

    void loadModelIntoBuffer()
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        uint32_t verticesSize = this->vertices.size() * sizeof(VertexPosNormalColorTex);
        uint32_t indicesSize = this->indices.size() * sizeof(uint32_t);

        createBuffer(ctxt.device,
                     ctxt.physicalDevice,
                     verticesSize + indicesSize,
                     VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     this->buffer,
                     this->bufferMemory);

        void *pLocalMem;
        /* copy vertices */
        vkMapMemory(ctxt.device, this->bufferMemory, 0, verticesSize, 0, &pLocalMem);
        memcpy(pLocalMem, this->vertices.data(), verticesSize);
        vkUnmapMemory(ctxt.device, this->bufferMemory);

        /* copy indices */
        vkMapMemory(ctxt.device, this->bufferMemory, verticesSize, indicesSize, 0, &pLocalMem);
        memcpy(pLocalMem, this->indices.data(), indicesSize);
        vkUnmapMemory(ctxt.device, this->bufferMemory);
    }
};


int main()
{
    Demo demo;
    try
    {
        demo.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}