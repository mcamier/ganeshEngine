#ifndef GE_VULKAN_MEMORY_MANAGER_H
#define GE_VULKAN_MEMORY_MANAGER_H

#include <vulkan/vulkan.h>

#include <vector>

#include "../../common/managers.hpp"
#include "../../vulkan/manager.hpp"
#include "../helper.hpp"
#include "../geometry.hpp"
#include "common.hpp"

using ge::vulkan::VulkanContextManager;

namespace ge {
namespace vulkan {
namespace memory {

//
// Stores values required for the VulkanContextManager's initialization
struct VulkanMemoryManagerInitializeArgs_t {
    uint64_t chunkSize;
    uint32_t poolSize;
};


template<typename PTR, typename SIZE>
void _fillMemory(VkDeviceMemory memory, uint64_t offset, PTR ptr, SIZE size) {
    void *pLocalMem;
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    vkMapMemory(ctxt.device, memory, offset, size, 0, &pLocalMem);
    memcpy(pLocalMem, ptr, size);
    vkUnmapMemory(ctxt.device, memory);

    return;
}

template<typename PTR, typename SIZE, typename... Args>
void _fillMemory(VkDeviceMemory memory, uint64_t offset, PTR ptr, SIZE size, Args... args) {
    void *pLocalMem;
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    vkMapMemory(ctxt.device, memory, offset, size, 0, &pLocalMem);
    memcpy(pLocalMem, ptr, size);
    vkUnmapMemory(ctxt.device, memory);

    uint64_t nextOffset = offset + size;

    // recursive call of the method until paramater pack is not empty
    _fillMemory(memory, nextOffset, args...);

    return;
}


template<typename PTR, typename SIZE>
uint64_t _sumRequiredSize(PTR ptr, SIZE size) {
    return size;
}

template<typename PTR, typename SIZE, typename... Args>
uint64_t _sumRequiredSize(PTR ptr, SIZE size, Args... args) {
    return size + _sumRequiredSize(args...);
}



// Responsible of managing eagerly allocated memory chunks for vulkan resources in order to avoid multiple
// vkDeviceMemory creation
class VulkanMemoryManager :
        public SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t> {
    friend SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t>;

private:
    // Amount of memory chunk allocated during initialization
    uint64_t chunkSize = 0;
    // Size of a single memory chunk
    uint32_t poolSize = 0;
    // store informations about each memory chunk available in the pool
    std::vector<memoryChunk_t> memoryPool;
    // Store collection of first node of linked list of type memoryAlloc_t
    // the collection is the same size as the amount of memory chunk
    std::vector<memoryAlloc_t *> allocations;

protected:
    VulkanMemoryManager() = default;

    void vInit(VulkanMemoryManagerInitializeArgs_t args) override;

    void vDestroy() override;

public:
    VulkanMemoryManager(const VulkanMemoryManager &) = delete;

    VulkanMemoryManager &operator=(const VulkanMemoryManager &) = delete;

    void vUpdate() override {}

    // This method will search into its memory pool a place to sub allocate memory for the required size
    // No device memory allocation occurs during this call, a new buffer is created and bound to a specific
    // memory location (memory allocation occurs during initialization of the manager)
    memoryAllocId allocateBuffer(uint64_t size, VkBufferUsageFlags usage);

    // Is like the non templated version of the method allocateBuffer, except this one will copy the provided datas
    // into the buffer
    template<typename... Args>
    memoryAllocId allocateBuffer(uint64_t size, VkBufferUsageFlags usage, void *ptr, uint64_t dataSize, Args... args) {
        memoryAllocId allocId = this->allocateWithPolicy<BufferAllocatorPolicy>(size, usage);

        memoryAlloc_t *memoryAlloc = nullptr;
        VkDeviceMemory memory;
        getMemoryAllocation(allocId, &memoryAlloc, &memory);
        uint64_t memOffset = memoryAlloc->memoryChunkOffset + memoryAlloc->alignmentOffset;

        uint64_t requiredSize = _sumRequiredSize(ptr, dataSize, args...);
        if (requiredSize > memoryAlloc->getDataSize()) {
            REP_FATAL("memory allocation is too small", ge::utils::LogChannelBitsFlag::DEFAULT)
        }

        _fillMemory(memory, memOffset, ptr, size, args...);

        return allocId;
    }

    memoryAllocId allocateUniform(uint64_t size);

    // Release a given sub allocation, it's release its bound buffer and make the space previously available for
    // later allocation request
    void free(memoryAllocId allocId);

    VkBuffer getBuffer(memoryAllocId allocId);

    // display the memory status in the log
    void dump();

private:
    // Allocate memory within the vulkanMemoryManager with a specific allocator
    template<typename allocator>
    memoryAllocId allocateWithPolicy(uint64_t size, VkBufferUsageFlags usage) {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        VkBuffer buffer = allocator::createBuffer(ctxt.device, size, usage);
        VkDeviceSize alignment = allocator::getAlignmentRequirement(ctxt.device, ctxt.physicalDevice, buffer);

        return findAvailableMemory(size, alignment, buffer);
    }

    void getMemoryAllocation(memoryAllocId allocId, memoryAlloc_t **memoryAlloc, VkDeviceMemory *memory);

    memoryAllocId findAvailableMemory(VkDeviceSize size, VkDeviceSize alignment, VkBuffer &buffer);
};


}
}
}

#endif //GE_RENDERMEMORYMANAGER_HPP
