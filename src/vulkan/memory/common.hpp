#ifndef GE_VULKAN_MEMORY_HEADER_H
#define GE_VULKAN_MEMORY_HEADER_H

#include <vulkan/vulkan.h>
#include <cstdint>

namespace ge {
namespace vulkan {
namespace memory {

typedef uint64_t memoryAllocId;


// memoryChunk_t Describes a memory chunk allocated and managed by the VulkanMemoryManager in order to provide fastest
// "sub allocations"
struct memoryChunk_t {
    VkBuffer                buffer;
    VkDeviceMemory          memory;
    uint64_t                size;
};


// memoryAlloc_t describes a memory block which belongs to a memory chunk managed by VulkanMemoryManager, it has
// virtually no allocation time
struct memoryAlloc_t {
    static memoryAllocId    lastId;

    // unique id, used to get access to the sub allocation or to free it througth appropriate methods of
    // VulkanMemoryManager
    memoryAllocId           id;
    // index of the memory chunk where the sub allocation belongs
    uint8_t memoryChunkIndex;
    // offset of the sub allocation within the chunk
    // Basically it's its position wihtin the chunk
    VkDeviceSize            memoryChunkOffset;
    // offset used to match the memory alignment constraint, should be add to memoryChunkOffset to get the real start
    // of the object stored in the sub allocation
    VkDeviceSize            alignmentOffset;
    // size of available storage of the sub allocation, it may not  represent the entire size of the allocation: to get
    // the full size of the allocation you should do the sum: allocationSize + alignmentOffset
    VkDeviceSize            allocationSize;
    VkBuffer                buffer;

    memoryAlloc_t *         pPrevious;
    memoryAlloc_t *         pNext;

    memoryAlloc_t() {
        id = lastId++;
        memoryChunkIndex = 0;
        memoryChunkOffset = 0;
        allocationSize = 0;
        alignmentOffset = 0;
        buffer = VK_NULL_HANDLE;
        pPrevious = nullptr;
        pNext = nullptr;
    }

    // compute the position of the end of the current memory block
    VkDeviceSize getEndPosition() const {
        return memoryChunkOffset + alignmentOffset + allocationSize;
    }

    VkDeviceSize getAlignedBeginPosition() const {
        return memoryChunkOffset + alignmentOffset;
    }

    VkDeviceSize getDataSize() const {
        return alignmentOffset + allocationSize;
    }
};


//
//
class UniformAllocatorPolicy {
private:
    UniformAllocatorPolicy() = default;

    ~UniformAllocatorPolicy() = default;

public:
    UniformAllocatorPolicy(const UniformAllocatorPolicy &) = delete;

    UniformAllocatorPolicy &operator=(const UniformAllocatorPolicy &) = delete;

    static VkDeviceSize getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer);

    static VkBuffer createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage);
};


//
//
class BufferAllocatorPolicy {
private:
    BufferAllocatorPolicy() = default;

    ~BufferAllocatorPolicy() = default;

public:
    BufferAllocatorPolicy(const BufferAllocatorPolicy &) = delete;

    BufferAllocatorPolicy &operator=(const BufferAllocatorPolicy &) = delete;

    static VkDeviceSize getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer);

    static VkBuffer createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage);
};

}
}
}

#endif //GE_VULKAN_MEMORY_HEADER_H