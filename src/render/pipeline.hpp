#ifndef RENDERENGINEPLAYGROUND_PIPELINE_HPP
#define RENDERENGINEPLAYGROUND_PIPELINE_HPP

#include <vector>

#include <vulkan/vulkan.h>

#include "geometry.hpp"
#include "initializers.hpp"

namespace rep
{

struct VertexPosNormalColorTex; // fast forward

using initializer::ShaderStageCreateInfo;
using initializer::InputAssemblyStateCreateInfo;
using initializer::ViewportStateCreateInfo;
using initializer::RasterizationStateCreateInfo;
using initializer::MultisampleStateCreateInfo;
using initializer::ColorBlendStateCreateInfo;
using initializer::VertexInputInfo;
using initializer::DescriptorSetLayoutInfo;

class Pipeline
{
public:
    class Builder;

    friend class Builder;

private:
    VkDevice                                device = VK_NULL_HANDLE;

    VkPipeline                              pipeline = VK_NULL_HANDLE;
    VkPipelineLayout                        pipelineLayout = VK_NULL_HANDLE;
    VkDescriptorPool                        descriptorPool = VK_NULL_HANDLE;
    std::vector<VkDescriptorSetLayout>      descriptorSetLayouts;
    std::vector<VkDescriptorSet>            descriptorSets;

public:
    void release();

    VkPipeline& getPipeline()
    {
        return this->pipeline;
    }

    VkPipelineLayout getPipelineLayout()
    {
        return this->pipelineLayout;
    }

    uint32_t getDesciptorSetCount()
    {
        return this->descriptorSets.size();
    }

    const VkDescriptorSet* const getDescriptorSets()
    {
        return this->descriptorSets.data();
    }

    const VkDescriptorSet& getDescriptorSet(uint32_t index)
    {
        return this->descriptorSets[index];
    }
};


class Pipeline::Builder
{

private:
    VkDevice                                device = VK_NULL_HANDLE;
    VkRenderPass                            renderPass = VK_NULL_HANDLE;
    const char *                            vertexShaderFilename = nullptr;
    const char *                            fragmentShaderFilename = nullptr;
    bool                                    useGeometryShader = false;
    const char *                            geometryShaderFilename = nullptr;
    InputAssemblyStateCreateInfo            inputAssemblyStateCreateInfo;
    ViewportStateCreateInfo                 viewportStateCreateInfo;
    RasterizationStateCreateInfo            rasterizationStateCreateInfo;
    MultisampleStateCreateInfo              multisampleStateCreateInfo;
    ColorBlendStateCreateInfo               colorBlendStateCreateInfo;
    VertexInputInfo                         vertexInputInfo;
    bool                                    hasDescriptorSetLayout = false;
    std::vector<DescriptorSetLayoutInfo>    descriptorSetLayoutsInfo;

public:
    Builder() :
            inputAssemblyStateCreateInfo(InputAssemblyStateCreateInfo()),
            viewportStateCreateInfo(ViewportStateCreateInfo({800, 600})),
            rasterizationStateCreateInfo(RasterizationStateCreateInfo()),
            multisampleStateCreateInfo(MultisampleStateCreateInfo()),
            colorBlendStateCreateInfo(ColorBlendStateCreateInfo())
    {}

    Builder &setDevice(VkDevice device);

    Builder &setVertexShader(const char *filename);

    Builder &setFragmentShader(const char *filename);

    Builder &setGeometryShader(const char *filename);

    Builder &setInputAssembly(InputAssemblyStateCreateInfo createInfo);

    Builder &setViewport(ViewportStateCreateInfo createInfo);

    Builder &setRasterization(RasterizationStateCreateInfo createInfo);

    Builder &setMultisample(MultisampleStateCreateInfo createInfo);

    Builder &setColorBlend(ColorBlendStateCreateInfo createInfo);

    Builder &setVertexInputBinding(VertexInputInfo createInfo);

    Builder &setRenderPass(VkRenderPass renderPass);

    Builder &addDescriptorSet(DescriptorSetLayoutInfo descriptorSetLayoutInfo);

    Pipeline build();
};

} // namespace rep

#endif //RENDERENGINEPLAYGROUND_PIPELINE_HPP
