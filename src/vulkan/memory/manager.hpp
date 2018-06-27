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

typedef VulkanMemoryStrategy<DefaultBufferCreationPolicy,
        DefaultMemoryAlignementPolicy,
        DefaultMemorySizePredictorPolicy,
        DefaultMemoryFillerPolicy> DefaultMemoryStrategy;

typedef VulkanMemoryStrategy<DefaultBufferCreationPolicy,
        DefaultMemoryAlignementPolicy,
        UniformBufferMemorySizePredictorPolicy,
        UniformBufferMemoryFillerPolicy> UniformBufferMemoryStrategy;

//
// Stores values required for the VulkanContextManager's initialization
struct VulkanMemoryManagerInitializeArgs_t {
    uint64_t chunkSize;
    uint32_t poolSize;
};


// Responsible of managing eagerly allocated memory chunks for vulkan resources in order to avoid multiple
// vkDeviceMemory creation
class VulkanMemoryManager :
        public SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t> {
    friend SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t>;

private:
    DefaultMemoryStrategy defaultMemoryStrategy;
    UniformBufferMemoryStrategy uniformBufferMemoryStrategy;
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


    template<typename... Args>
    memoryAllocId allocate(VkBufferUsageFlags usage, void *dataPtr, uint64_t dataSize, Args... otherDatas) {
        return allocate(defaultMemoryStrategy, usage, dataPtr, dataSize, otherDatas...);
    }


    template<typename... Args>
    memoryAllocId allocateUniformBuffer(VkBufferUsageFlags usage, void *dataPtr, uint64_t dataSize, Args... otherDatas) {
        return allocate(uniformBufferMemoryStrategy, usage, dataPtr, dataSize, otherDatas...);
    }


    template<
            typename MemoryStrategy,
            typename... Args
    >
    memoryAllocId allocate(MemoryStrategy strategy, VkBufferUsageFlags usage, void *dataPtr, uint64_t dataSize, Args... otherDatas) {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        memoryAlloc_t *memoryAlloc = nullptr;

        uint64_t allocationSize = strategy.getSize(dataPtr, dataSize, otherDatas...);
        VkBuffer buffer = strategy.createBuffer(ctxt.device, allocationSize, usage);
        VkDeviceSize alignment = strategy.getAlignmentRequirement(ctxt.device, ctxt.physicalDevice,
                                                                               buffer);

        memoryAlloc = findAvailableMemory(allocationSize, alignment, buffer);
        VkDeviceMemory deviceMemory = memoryPool[memoryAlloc->memoryChunkIndex].memory;

        strategy.fillMemory(deviceMemory,
                                         memoryAlloc->getDataBeginPosition(),
                                         dataPtr,
                                         dataSize,
                                         otherDatas...);

        return memoryAlloc->id;
    }


    // Release a given sub allocation, it's release its bound buffer and make the space previously available for
    // later allocation request
    void free(memoryAllocId allocId);

    AllocationInfo getAllocationInfo(memoryAllocId allocId);

    // display the memory status in the log
    void dump();

private:
    void getMemoryAllocation(memoryAllocId allocId, memoryAlloc_t **memoryAlloc);

    memoryAlloc_t *findAvailableMemory(VkDeviceSize size, VkDeviceSize alignment, VkBuffer &buffer);
};


}
}
}

#endif //GE_RENDERMEMORYMANAGER_HPP
