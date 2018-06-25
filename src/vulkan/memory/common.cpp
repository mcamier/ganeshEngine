#include "common.hpp"

#include <stdexcept>

namespace ge {
namespace vulkan {
namespace memory {


VkDeviceSize
UniformAllocatorPolicy::getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    return deviceProperties.limits.minUniformBufferOffsetAlignment;
}


VkBuffer UniformAllocatorPolicy::createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage) {
    VkBuffer buffer;
    // we create a specific buffer for the new "sub-allocation"
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (VK_SUCCESS != vkCreateBuffer(device, &bufferInfo, nullptr, &buffer)) {
        throw std::runtime_error("[UniformAllocatorPolicy::createBuffer] failed to create vertex buffer");
    }
    return buffer;
}

VkDeviceSize BufferAllocatorPolicy::getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice,
                                                            VkBuffer buffer) {
    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
    return memoryRequirements.alignment;
}

VkBuffer BufferAllocatorPolicy::createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage) {
    VkBuffer buffer;
    // we create a specific buffer for the new "sub-allocation"
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (VK_SUCCESS != vkCreateBuffer(device, &bufferInfo, nullptr, &buffer)) {
        throw std::runtime_error("[BufferAllocatorPolicy::createBuffer] failed to create vertex buffer");
    }
    return buffer;
}

}
}
}
