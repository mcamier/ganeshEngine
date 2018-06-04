#ifndef RENDERENGINEPLAYGROUND_GEOMETRY_HPP
#define RENDERENGINEPLAYGROUND_GEOMETRY_HPP

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

namespace rep
{

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};


struct VertexPosColorTex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

}

#endif //RENDERENGINEPLAYGROUND_GEOMETRY_HPP
