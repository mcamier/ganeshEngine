#ifndef GE_INITIALIZERS_HPP
#define GE_INITIALIZERS_HPP

#include <vector>

#include <vulkan/vulkan.h>


namespace ge
{
namespace vulkan
{
namespace helper
{

class DescriptorSetLayoutInfo
{
private:
    std::vector<VkDescriptorSetLayoutBinding> bindings;

public:
    DescriptorSetLayoutInfo &addBinding(VkDescriptorType type,
                                           VkShaderStageFlags shader,
                                           uint32_t bindingIndex,
                                           uint32_t count);

    DescriptorSetLayoutInfo &addBinding(VkDescriptorType type,
                                           VkShaderStageFlags shader,
                                           uint32_t bindingIndex);

    std::vector<VkDescriptorSetLayoutBinding>& get()
    {
        return this->bindings;
    }
};


class ShaderStageCreateInfo
{
private:
    VkPipelineShaderStageCreateInfo stageInfo = {};

public:
    ShaderStageCreateInfo();

    VkPipelineShaderStageCreateInfo &get()
    {
        return this->stageInfo;
    }

    ShaderStageCreateInfo &withShaderModule(VkShaderModule module)
    {
        stageInfo.module = module;
        return *this;
    }

    ShaderStageCreateInfo &asVertexShader()
    {
        stageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        return *this;
    }

    ShaderStageCreateInfo &asGeometryShader()
    {
        stageInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
        return *this;
    }

    ShaderStageCreateInfo &asFragmentShader()
    {
        stageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        return *this;
    }
};


class ViewportStateCreateInfo
{
private:
    VkRect2D scissor;
    VkViewport viewport;
    VkPipelineViewportStateCreateInfo viewportCreateInfo;

public:
    ViewportStateCreateInfo(VkExtent2D extent);

    VkPipelineViewportStateCreateInfo get()
    {
        return viewportCreateInfo;
    }
};


class InputAssemblyStateCreateInfo
{
private:
    VkPipelineInputAssemblyStateCreateInfo assemblyStateInfo = {};

public:
    InputAssemblyStateCreateInfo();

    VkPipelineInputAssemblyStateCreateInfo get()
    {
        return this->assemblyStateInfo;
    }
};


class RasterizationStateCreateInfo
{
private:
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};

public:
    RasterizationStateCreateInfo();

    VkPipelineRasterizationStateCreateInfo get()
    {
        return this->rasterizationStateCreateInfo;
    }
};


class MultisampleStateCreateInfo
{
private:
    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};

public:
    MultisampleStateCreateInfo();

    VkPipelineMultisampleStateCreateInfo get()
    {
        return this->multisampleStateCreateInfo;
    }
};


class ColorBlendStateCreateInfo
{
private:
    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
    std::vector<VkPipelineColorBlendAttachmentState> blendAttachments;

public:
    ColorBlendStateCreateInfo();

    VkPipelineColorBlendStateCreateInfo get()
    {
        return this->colorBlendStateCreateInfo;
    }
};

class VertexInputInfo
{

private:
    VkVertexInputBindingDescription bindingDesc = {};
    std::vector<VkVertexInputAttributeDescription> attributes;


public:
    VertexInputInfo();

    template<typename VERTEX>
    static VertexInputInfo from()
    {
        VertexInputInfo result;
        result.attributes = VERTEX::getAttributeDescriptions();
        result.bindingDesc.stride = sizeof(VERTEX);
        return result;
    }

    VkVertexInputBindingDescription getBindingDescription()
    {
        return this->bindingDesc;
    }

    std::vector<VkVertexInputAttributeDescription> getAttributesDescription()
    {
        return this->attributes;
    }
};

} // namespace helper
} // namespace vulkan
} // namespace ge


#endif //GE_INITIALIZERS_HPP
