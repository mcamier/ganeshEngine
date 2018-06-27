#include "common.hpp"

namespace ge {
namespace vulkan {
namespace memory {


//
//
VkDeviceSize DefaultMemoryAlignementPolicy::getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice,
                                                                    VkBuffer buffer) {
    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
    return memoryRequirements.alignment;
}


//
//
VkBuffer DefaultBufferCreationPolicy::createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage) {
    VkBuffer buffer;

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
