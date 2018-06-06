#ifndef RENDERENGINEPLAYGROUND_GEOMETRY_HPP
#define RENDERENGINEPLAYGROUND_GEOMETRY_HPP

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include "../common/vulkan/vulkan_helpers.hpp"

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
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};


struct VertexPosNormalColorTex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};


struct meshBufferOffset_t
{
    uint64_t meshOffset;
    uint64_t meshRelativeIndicesOffset;
};


struct meshInstance_t
{
    uint32_t vertexSize = sizeof(VertexPosColorTex);
    uint32_t indexSize = sizeof(uint32_t);

    uint32_t verticeCount;
    VertexPosColorTex *vertices;
    uint32_t indexCount;
    uint32_t *indices;
    /**
     * pipeline to use, if value set to -1, the renderManager will use its default pipeline
     */
    uint32_t pipelineId = -1;

    /**
     * for renderManager internal use
     */
    meshBufferOffset_t offset;
};

template<typename T>
struct pipelineInfosBuilder {
    static pipelineInfos_t build() {
        pipelineInfos_t infos = {};
        infos.vertexInputBindingDescription = T::getBindingDescription();
        infos.attributeDescriptions = T::getAttributeDescriptions();
        return infos;
    }
};

}

#endif //RENDERENGINEPLAYGROUND_GEOMETRY_HPP