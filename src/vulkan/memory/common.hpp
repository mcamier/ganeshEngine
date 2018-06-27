#ifndef GE_VULKAN_MEMORY_HEADER_H
#define GE_VULKAN_MEMORY_HEADER_H

#include <vulkan/vulkan.h>
#include <cstdint>
#include <stdexcept>

#include "../../vulkan/manager.hpp"

using ge::vulkan::VulkanContextManager;

namespace ge {
namespace vulkan {
namespace memory {

typedef uint64_t memoryAllocId;


// memoryChunk_t Describes a memory chunk allocated and managed by the VulkanMemoryManager in order to provide fastest
// "sub allocations"
struct memoryChunk_t {
    VkBuffer buffer;
    VkDeviceMemory memory;
    uint64_t size;
};


// memoryAlloc_t describes a memory block which belongs to a memory chunk managed by VulkanMemoryManager, it has
// virtually no allocation time
struct memoryAlloc_t {
    static memoryAllocId lastId;

    // unique id, used to get access to the sub allocation or to free it througth appropriate methods of
    // VulkanMemoryManager
    memoryAllocId id;
    // index of the memory chunk where the sub allocation belongs
    uint8_t memoryChunkIndex;
    // offset of the sub allocation within the chunk
    // Basically it's its position wihtin the chunk
    VkDeviceSize memoryChunkOffset;
    // offset used to match the memory alignment constraint, should be add to memoryChunkOffset to get the real start
    // of the object stored in the sub allocation
    VkDeviceSize alignmentOffset;
    // size of available storage of the sub allocation, it may not  represent the entire size of the allocation: to get
    // the full size of the allocation you should do the sum: allocationSize + alignmentOffset
    VkDeviceSize allocationSize;

    VkBuffer buffer;

    memoryAlloc_t *pPrevious;
    memoryAlloc_t *pNext;

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

    VkDeviceSize getDataBeginPosition() const {
        return memoryChunkOffset + alignmentOffset;
    }

    VkDeviceSize getDataSize() const {
        return alignmentOffset + allocationSize;
    }
};


//
//
struct AllocationInfo {
    memoryAllocId       id;
    VkBuffer            buffer;

    explicit AllocationInfo(memoryAlloc_t& memoryAlloc) {
        id = memoryAlloc.id;
        buffer = memoryAlloc.buffer;
    }
};


template<typename PTR, typename SIZE>
uint64_t _sumRequiredSize(PTR ptr, SIZE size) {
    return size;
}

template<typename PTR, typename SIZE, typename... Args>
uint64_t _sumRequiredSize(PTR ptr, SIZE size, Args... args) {
    return size + _sumRequiredSize(args...);
}


//
//
template<typename BufferCreationPolicy,
        typename MemoryAlignementPolicy,
        typename MemorySizePredictorPolicy,
        typename MemoryFillerPolicy>
class VulkanMemoryStrategy :
        public BufferCreationPolicy,
        public MemorySizePredictorPolicy,
        public MemoryFillerPolicy,
        public MemoryAlignementPolicy {
};

//
//
struct DefaultMemoryAlignementPolicy {
    static VkDeviceSize getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer);
};


//
//
struct DefaultBufferCreationPolicy {
    static VkBuffer createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage);
};


//
//
struct DefaultMemorySizePredictorPolicy {
    // Default memory size prediction is quiet obvious, it is the sum of all data's sizes
    //
    // Note: Args... is a parameter pack supposed to contains many couple of a pointer to a data, and the size of this
    //       data
    // Note: This size doesn't include the pre-pedded padding bytes required to get date in good memory alignement
    template<typename... Args>
    static VkDeviceSize getSize(void *dataPtr, uint64_t dataSize, Args... otherDatas) {
        return _sumRequiredSize(dataPtr, dataSize, otherDatas...);
    }
};


//
//
struct UniformBufferMemorySizePredictorPolicy {
    // Memory size prediction for uniform buffer is not as obvious as the default one
    // It's basically the same sum of data's size, but this time if a data's size is smaller than
    // deviceProperties.limits.minUniformBufferOffsetAlignment, a padding amount if byte is append before the next
    // data's position, increasing the necessary space to allocate.
    //
    // Note: Args... is a parameter pack supposed to contains many couple of a pointer to a data, and the size of this
    //       data
    // Note: This size doesn't include the pre-pedded padding bytes required to get date in good memory alignement
    template<typename... Args>
    static VkDeviceSize getSize(void *dataPtr, uint64_t dataSize, Args... args) {
        // TODO implement me
        // VkPhysicalDeviceProperties deviceProperties;
        // vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
        // return deviceProperties.limits.minUniformBufferOffsetAlignment;
        return 0;
    }
};


template<typename PTR, typename SIZE>
void _fillMemory(VkDeviceMemory memory, uint64_t offset, PTR dataPtr, SIZE dataSize) {
    void *pLocalMem;
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    vkMapMemory(ctxt.device, memory, offset, dataSize, 0, &pLocalMem);
    memcpy(pLocalMem, dataPtr, dataSize);
    vkUnmapMemory(ctxt.device, memory);
}

template<typename PTR, typename SIZE, typename... Args>
void _fillMemory(VkDeviceMemory memory, uint64_t offset, PTR dataPtr, SIZE dataSize, Args... otherDatas) {
    void *pLocalMem;
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    vkMapMemory(ctxt.device, memory, offset, dataSize, 0, &pLocalMem);
    memcpy(pLocalMem, dataPtr, dataSize);
    vkUnmapMemory(ctxt.device, memory);

    uint64_t nextOffset = offset + dataSize;

    // recursive call of the method until paramater pack is not empty
    _fillMemory(memory, nextOffset, otherDatas...);
}


//
//
struct DefaultMemoryFillerPolicy {
    template<typename PTR, typename SIZE, typename... Args>
    static void fillMemory(VkDeviceMemory memory, uint64_t offset, PTR dataPtr, SIZE dataSize, Args... otherDatas) {
        _fillMemory(memory, offset, dataPtr, dataSize, otherDatas...);
    }
};


//
//
struct UniformBufferMemoryFillerPolicy {
    template<typename PTR, typename SIZE, typename... Args>
    static void fillMemory(VkDeviceMemory memory, uint64_t offset, PTR dataPtr, SIZE dataSize, Args... otherDatas) {
        // TODO implement me
        return;
    }
};


}
}
}

#endif //GE_VULKAN_MEMORY_HEADER_H