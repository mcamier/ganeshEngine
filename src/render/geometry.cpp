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

std::array<VkVertexInputAttributeDescription, 3> VertexPosColorTex::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 3> attributes = {};
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[0].offset = offsetof(VertexPosColorTex, pos);

    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[1].offset = offsetof(VertexPosColorTex, color);

    attributes[2].binding = 0;
    attributes[2].location = 2;
    attributes[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributes[2].offset = offsetof(VertexPosColorTex, texCoord);

    return attributes;
}
}