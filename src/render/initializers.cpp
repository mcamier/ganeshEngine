#include "initializers.hpp"

namespace rep
{

namespace initializer
{

ShaderStageCreateInfo::ShaderStageCreateInfo()
{
    stageInfo = {};
    stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stageInfo.module = VK_NULL_HANDLE;
    stageInfo.pName = "main";
}


ViewportStateCreateInfo::ViewportStateCreateInfo(VkExtent2D extent)
{
    scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = extent;

    viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    viewport.x = 0.0f;
    viewport.y = 0.0f;

    viewportCreateInfo = {};
    viewportCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportCreateInfo.viewportCount = 1;
    viewportCreateInfo.pViewports = &viewport;
    viewportCreateInfo.scissorCount = 1;
    viewportCreateInfo.pScissors = &scissor;
}


InputAssemblyStateCreateInfo::InputAssemblyStateCreateInfo()
{
    assemblyStateInfo = {};
    assemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assemblyStateInfo.primitiveRestartEnable = VK_FALSE;
    assemblyStateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}


RasterizationStateCreateInfo::RasterizationStateCreateInfo()
{
    rasterizationStateCreateInfo = {};
    rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_LINE;
    rasterizationStateCreateInfo.lineWidth = 1.0f;
    rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
}

MultisampleStateCreateInfo::MultisampleStateCreateInfo()
{
    multisampleStateCreateInfo = {};
    multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
    multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}


ColorBlendStateCreateInfo::ColorBlendStateCreateInfo()
{
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    this->blendAttachments.resize(1);
    this->blendAttachments[0] = colorBlendAttachment;

    colorBlendStateCreateInfo = {};
    colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    colorBlendStateCreateInfo.attachmentCount = this->blendAttachments.size();
    colorBlendStateCreateInfo.pAttachments = this->blendAttachments.data();
    colorBlendStateCreateInfo.blendConstants[0] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[1] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[2] = 0.0f;
    colorBlendStateCreateInfo.blendConstants[3] = 0.0f;
}

VertexInputInfo::VertexInputInfo()
{
    bindingDesc = {};
    bindingDesc.binding = 0;
    bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindingDesc.stride = 0;
}


DescriptorSetLayoutInfo &DescriptorSetLayoutInfo::addBinding(VkDescriptorType type,
                                                             VkShaderStageFlags shader,
                                                             uint32_t bindingIndex,
                                                             uint32_t count)
{
    VkDescriptorSetLayoutBinding binding = {};
    binding.descriptorType = type;
    binding.stageFlags = shader;
    binding.binding = bindingIndex;
    binding.descriptorCount = count;
    this->bindings.push_back(binding);

    return *this;
}

DescriptorSetLayoutInfo &DescriptorSetLayoutInfo::addBinding(VkDescriptorType type,
                                                             VkShaderStageFlags shader,
                                                             uint32_t bindingIndex)
{
    return this->addBinding(type, shader, bindingIndex, 1);
}

} // namespace initializer

} // namespace rep