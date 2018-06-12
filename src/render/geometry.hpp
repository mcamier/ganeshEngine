#ifndef RENDERENGINEPLAYGROUND_GEOMETRY_HPP
#define RENDERENGINEPLAYGROUND_GEOMETRY_HPP

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include "vulkan_helpers.hpp"

namespace rep
{

struct ViewProjTransformation
{
    glm::mat4 view;
    glm::mat4 proj;
};

struct ModelTransformation
{
    glm::mat4 model;
};

struct VertexPosNormalColorTex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};


struct meshBufferOffset_t
{
    uint64_t meshOffset;
    uint64_t meshRelativeIndicesOffset;
};


struct vulkanContextInfos_t
{
    const VkInstance &        vulkanInstance;
    const VkSurfaceKHR &      surface;
    const VkPhysicalDevice &  physicalDevice;
    const VkDevice &          device;
    const VkQueue &           graphicQueue;
    const VkQueue &           presentQueue;
    const VkCommandPool &     graphicCommandPool;
    const VkRenderPass &      renderPass;
    const VkSwapchainKHR &    swapchain;
};

}

#endif //RENDERENGINEPLAYGROUND_GEOMETRY_HPP