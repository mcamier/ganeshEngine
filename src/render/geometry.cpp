#include "geometry.hpp"

namespace rep
{

VkVertexInputBindingDescription VertexPosColorTex::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDesc = {};
    bindingDesc.binding = 0;
    bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindingDesc.stride = sizeof(VertexPosColorTex);
    return bindingDesc;
}

std::vector<VkVertexInputAttributeDescription> VertexPosColorTex::getAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> attributes(3);
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[0].offset = offsetof(VertexPosColorTex, position);

    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[1].offset = offsetof(VertexPosColorTex, color);

    attributes[2].binding = 0;
    attributes[2].location = 2;
    attributes[2].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[2].offset = offsetof(VertexPosColorTex, texCoord);

    return attributes;
}

VkVertexInputBindingDescription VertexPosNormalColorTex::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDesc = {};
    bindingDesc.binding = 0;
    bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindingDesc.stride = sizeof(VertexPosNormalColorTex);
    return bindingDesc;
}

std::vector<VkVertexInputAttributeDescription> VertexPosNormalColorTex::getAttributeDescriptions()
{
    std::vector<VkVertexInputAttributeDescription> attributes(4);
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[0].offset = offsetof(VertexPosNormalColorTex, position);

    attributes[1].binding = 0;
    attributes[1].location = 0;
    attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[1].offset = offsetof(VertexPosNormalColorTex, normal);

    attributes[2].binding = 0;
    attributes[2].location = 1;
    attributes[2].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[2].offset = offsetof(VertexPosNormalColorTex, color);

    attributes[3].binding = 0;
    attributes[3].location = 1;
    attributes[3].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[3].offset = offsetof(VertexPosNormalColorTex, texCoord);

    return attributes;
}
}