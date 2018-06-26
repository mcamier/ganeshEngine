#include <array>
#include "pipeline.hpp"

using ge::vulkan::helper::createShaderModule;
using ge::utils::readFile;



namespace ge {
namespace vulkan {

void Pipeline::release() {
    for (auto &descriptorSetLayout: descriptorSetLayouts) {
        vkDestroyDescriptorSetLayout(this->device, descriptorSetLayout, nullptr);
    }
    vkDestroyDescriptorPool(this->device, this->descriptorPool, nullptr);
    vkDestroyPipelineLayout(this->device, this->pipelineLayout, nullptr);
    vkDestroyPipeline(this->device, this->pipeline, nullptr);
}

Pipeline::Builder &Pipeline::Builder::setDevice(VkDevice device) {
    this->device = device;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setVertexShader(const char *filename) {
    this->vertexShaderFilename = filename;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setFragmentShader(const char *filename) {
    this->fragmentShaderFilename = filename;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setGeometryShader(const char *filename) {
    this->geometryShaderFilename = filename;
    this->useGeometryShader = true;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setInputAssembly(InputAssemblyStateCreateInfo createInfo) {
    this->inputAssemblyStateCreateInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setViewport(ViewportStateCreateInfo createInfo) {
    this->viewportStateCreateInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setRasterization(RasterizationStateCreateInfo createInfo) {
    this->rasterizationStateCreateInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setMultisample(MultisampleStateCreateInfo createInfo) {
    this->multisampleStateCreateInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setColorBlend(ColorBlendStateCreateInfo createInfo) {
    this->colorBlendStateCreateInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setRenderPass(VkRenderPass renderPass) {
    this->renderPass = renderPass;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::setVertexInputBinding(VertexInputInfo createInfo) {
    this->vertexInputInfo = createInfo;
    return *this;
}

Pipeline::Builder &Pipeline::Builder::addDescriptorSet(DescriptorSetLayoutInfo createInfo) {
    this->hasDescriptorSetLayout = true;
    this->descriptorSetLayoutsInfo.push_back(createInfo);
    return *this;
}

Pipeline Pipeline::Builder::build() {
    VkResult result;
    Pipeline pipeline;
    if (this->device == VK_NULL_HANDLE) {
        throw std::runtime_error("call Pipeline::Builder::setDevice prior to Pipeline::Builder::build");
    }
    if (this->vertexShaderFilename == nullptr) {
        throw std::runtime_error("call Pipeline::Builder::setVertexShader prior to Pipeline::Builder::build");
    }
    if (this->fragmentShaderFilename == nullptr) {
        throw std::runtime_error("call Pipeline::Builder::setFragmentShader prior to Pipeline::Builder::build");
    }

    pipeline.device = device;
    VkShaderModule vertexShaderModule = VK_NULL_HANDLE;
    VkShaderModule geometryShaderModule = VK_NULL_HANDLE;
    VkShaderModule fragmentShaderModule = VK_NULL_HANDLE;

    int shaderStageCount = (this->useGeometryShader) ? 3 : 2;
    std::vector<ShaderStageCreateInfo> shaderStagesCreateInfo(shaderStageCount);

    createShaderModule(this->device, readFile(this->vertexShaderFilename), &vertexShaderModule);
    shaderStagesCreateInfo[0] = ShaderStageCreateInfo().asVertexShader().withShaderModule(vertexShaderModule);

    createShaderModule(this->device, readFile(this->fragmentShaderFilename), &fragmentShaderModule);
    shaderStagesCreateInfo[1] = ShaderStageCreateInfo().asFragmentShader().withShaderModule(fragmentShaderModule);

    if (this->useGeometryShader) {
        createShaderModule(this->device, readFile(this->geometryShaderFilename), &geometryShaderModule);
        shaderStagesCreateInfo[2] = ShaderStageCreateInfo().asGeometryShader().withShaderModule(geometryShaderModule);
    }

    std::vector<VkPipelineShaderStageCreateInfo> stagesCreateInfo(shaderStageCount);
    for (int i = 0; i < shaderStagesCreateInfo.size(); i++) {
        stagesCreateInfo[i] = shaderStagesCreateInfo[i].get();
    }

    VkPipelineViewportStateCreateInfo viewportCreateInfo = this->viewportStateCreateInfo.get();
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = this->multisampleStateCreateInfo.get();
    VkPipelineInputAssemblyStateCreateInfo assemblyStateInfo = this->inputAssemblyStateCreateInfo.get();
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = this->rasterizationStateCreateInfo.get();
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = this->colorBlendStateCreateInfo.get();

    /**
     * descriptor set layout
     */
    if (this->hasDescriptorSetLayout) {
        pipeline.descriptorSetLayouts.resize(this->descriptorSetLayoutsInfo.size());
        for (int i = 0; i < this->descriptorSetLayoutsInfo.size(); i++) {
            DescriptorSetLayoutInfo &descriptorSetLayoutInfo = this->descriptorSetLayoutsInfo[i];
            auto bindings = descriptorSetLayoutInfo.get();

            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = bindings.size();
            layoutInfo.pBindings = bindings.data();
            result = vkCreateDescriptorSetLayout(this->device, &layoutInfo, nullptr,
                                                 &(pipeline.descriptorSetLayouts[i]));
            ASSERT(result == VK_SUCCESS)

        }

        /**
         * descriptor pool
         * TODO is not dynamic
         */
        std::array<VkDescriptorPoolSize, 1> poolSizes = {};
        poolSizes[0].descriptorCount = 1;
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

        VkDescriptorPool descriptorPool;
        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.maxSets = 2;
        descriptorPoolCreateInfo.poolSizeCount = poolSizes.size();
        descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();
        result = vkCreateDescriptorPool(this->device, &descriptorPoolCreateInfo, nullptr, &pipeline.descriptorPool);
        ASSERT(result == VK_SUCCESS)


        VkDescriptorSetAllocateInfo descSetAllocInfo = {};
        descSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descSetAllocInfo.descriptorPool = pipeline.descriptorPool;
        descSetAllocInfo.descriptorSetCount = pipeline.descriptorSetLayouts.size();
        descSetAllocInfo.pSetLayouts = pipeline.descriptorSetLayouts.data();

        pipeline.descriptorSets.resize(pipeline.descriptorSetLayouts.size());
        result = vkAllocateDescriptorSets(this->device, &descSetAllocInfo, pipeline.descriptorSets.data());
        ASSERT(result == VK_SUCCESS)
    }

    /**
     * pipeline layout and pipeline creation
     */
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
    pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    if (this->hasDescriptorSetLayout) {
        pipelineLayoutCreateInfo.setLayoutCount = pipeline.descriptorSetLayouts.size();
        pipelineLayoutCreateInfo.pSetLayouts = pipeline.descriptorSetLayouts.data();
    } else {
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
    }
    pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
    pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
    result = vkCreatePipelineLayout(this->device, &pipelineLayoutCreateInfo, nullptr, &pipeline.pipelineLayout);
    ASSERT(result == VK_SUCCESS)

    auto inputBindingDescription = this->vertexInputInfo.getBindingDescription();
    auto inputAttibutesDescription = this->vertexInputInfo.getAttributesDescription();

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = inputAttibutesDescription.size();
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = inputAttibutesDescription.data();
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateCreateInfo.pVertexBindingDescriptions = &inputBindingDescription;

    VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCreateInfo.stageCount = stagesCreateInfo.size();
    pipelineCreateInfo.pStages = stagesCreateInfo.data();
    pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
    pipelineCreateInfo.pInputAssemblyState = &assemblyStateInfo;
    pipelineCreateInfo.pViewportState = &viewportCreateInfo;
    pipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
    pipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
    pipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
    pipelineCreateInfo.pDynamicState = nullptr;
    pipelineCreateInfo.layout = pipeline.pipelineLayout;
    pipelineCreateInfo.renderPass = this->renderPass;
    pipelineCreateInfo.subpass = 0;
    pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineCreateInfo.basePipelineIndex = -1;

    result = vkCreateGraphicsPipelines(this->device,
                                       VK_NULL_HANDLE,
                                       1,
                                       &pipelineCreateInfo,
                                       nullptr,
                                       &pipeline.pipeline);

    ASSERT(result == VK_SUCCESS)

    vkDestroyShaderModule(this->device, vertexShaderModule, nullptr);
    vkDestroyShaderModule(this->device, fragmentShaderModule, nullptr);
    if (this->useGeometryShader) {
        vkDestroyShaderModule(this->device, geometryShaderModule, nullptr);
    }

    return pipeline;
}

} // namespace vulkan
} // namespace ge