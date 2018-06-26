#include "manager.hpp"

#include <array>

#include "../../window/manager.hpp"
#include "../../common/log_utils.hpp"

using ge::vulkan::helper::createBuffer;
using ge::utils::LogChannelBitsFlag;

namespace ge {
namespace vulkan {
namespace memory {

uint64_t memoryAlloc_t::lastId = 0;


void VulkanMemoryManager::vInit(VulkanMemoryManagerInitializeArgs_t args)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    VkBufferUsageFlags bufferUsageFlags = VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
                                          VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                          VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
                                          VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
                                          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                                          VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                          VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                          VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
    REP_DEBUG("Vulkan memory pool : " << args.poolSize << " chunks, of " << args.chunkSize << " bytes each",
              LogChannelBitsFlag::DEFAULT)
    chunkSize = args.chunkSize;
    poolSize = args.poolSize;
    memoryPool.resize(args.poolSize);
    allocations.resize(args.poolSize);
    for (int i = 0; i < args.poolSize; i++)
    {
        memoryPool[i].size = chunkSize;
        createBuffer(ctxt.device,
                     ctxt.physicalDevice,
                     args.chunkSize,
                     bufferUsageFlags,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     memoryPool[i].buffer,
                     memoryPool[i].memory);
        REP_DEBUG("  chunk of " << args.chunkSize << " bytes allocated", LogChannelBitsFlag::DEFAULT)
    }
}

void VulkanMemoryManager::vDestroy()
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    // destroy all buffers allocated
    for (int chunk = 0; chunk < poolSize; chunk++)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr)
        {
            vkDestroyBuffer(ctxt.device, alloc->buffer, nullptr);
            alloc = alloc->pNext;
        }
    }

    // detroy the memory chunks
    for (int chunk = 0; chunk < poolSize; chunk++)
    {
        vkFreeMemory(ctxt.device, memoryPool[chunk].memory, nullptr);
        vkDestroyBuffer(ctxt.device, memoryPool[chunk].buffer, nullptr);
    }
    REP_DEBUG("VulkanMemoryManager destroyed", LogChannelBitsFlag::DEFAULT)
}


memoryAllocId VulkanMemoryManager::allocateBuffer(uint64_t size, VkBufferUsageFlags usage)
{
    return this->allocateWithPolicy<BufferAllocatorPolicy>(size, usage);
}


memoryAllocId VulkanMemoryManager::allocateUniform(uint64_t size)
{
    return this->allocateWithPolicy<UniformAllocatorPolicy>(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
}

memoryAllocId VulkanMemoryManager::findAvailableMemory(VkDeviceSize size, VkDeviceSize alignment, VkBuffer &buffer)
{
    // TODO loop on every chunk
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    memoryAllocId allocId = -1;
    uint8_t chunkIndex = 0;
    bool memoryLocationFound = false;

    memoryAlloc_t *newAlloc = new memoryAlloc_t();
    newAlloc->memoryChunkIndex = chunkIndex;
    newAlloc->memoryChunkOffset = 0;
    newAlloc->alignmentOffset = 0;
    newAlloc->allocationSize = size;
    newAlloc->buffer = buffer;

    memoryAlloc_t *current_alloc = allocations[chunkIndex];

    // No allocation already exists in this chunk
    if (current_alloc == nullptr)
    {
        allocations[chunkIndex] = newAlloc;

        vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory, 0);
        memoryLocationFound = true;
        allocId = allocations[chunkIndex]->id;
    }

    // Look up for enough room to allocate new memory block
    while (current_alloc != nullptr && !memoryLocationFound)
    {
        // compute the position of the end of the current memory block
        uint64_t position = current_alloc->getEndPosition();
        newAlloc->alignmentOffset = alignment - (position % alignment);

        if (current_alloc->pNext != nullptr)
        {
            // we are not at the end of linked list, but we check if there is a gap with enough room to host the
            // requested memory block
            memoryAlloc_t *next_alloc = current_alloc->pNext;
            uint64_t gap = next_alloc->memoryChunkOffset - position;
            if (gap >= newAlloc->alignmentOffset + size)
            {
                // the allocation fits between two previously allocated block
                // insert a node between two nodes
                newAlloc->memoryChunkOffset = position;
                newAlloc->pPrevious = current_alloc;
                newAlloc->pNext = next_alloc;
                current_alloc->pNext = newAlloc;
                next_alloc->pPrevious = newAlloc;

                vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory,
                                   newAlloc->getAlignedBeginPosition());
                memoryLocationFound = true;
                allocId = newAlloc->id;
            }
        }
        else
        {
            // we are at the end of the linked list, we check if there is enough room for the request memory block
            uint64_t lastGap = memoryPool[chunkIndex].size - position;
            if (lastGap >= newAlloc->alignmentOffset + size)
            {
                // the allocation fits between two previously allocated block
                // insert a node between two nodes
                newAlloc->memoryChunkOffset = position;
                newAlloc->pPrevious = current_alloc;
                newAlloc->pNext = nullptr;
                current_alloc->pNext = newAlloc;

                vkBindBufferMemory(ctxt.device, buffer, memoryPool[chunkIndex].memory,
                                   newAlloc->getAlignedBeginPosition());
                memoryLocationFound = true;
                allocId = newAlloc->id;
            }
        }
        current_alloc = current_alloc->pNext;
    }

    if (!memoryLocationFound)
    {
        delete newAlloc;
        throw std::runtime_error("Unable to find enough room to sub allocate memory");
    }
    return allocId;
}


void VulkanMemoryManager::free(memoryAllocId allocId)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    bool found = false;
    int chunk = 0;

    while (chunk < poolSize && !found)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && !found)
        {
            if (alloc->id == allocId)
            {
                found = true;
                vkDestroyBuffer(ctxt.device, alloc->buffer, nullptr);
                alloc->pPrevious->pNext = alloc->pNext;
                delete alloc;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }
}


void VulkanMemoryManager::dump()
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();

    REP_DEBUG("##################################", LogChannelBitsFlag::DEFAULT)
    REP_DEBUG("DUMP MEMORY CHUNK 0", LogChannelBitsFlag::DEFAULT)
    memoryAlloc_t *alloc = allocations[0];
    while (alloc != nullptr)
    {
        uint64_t position = alloc->memoryChunkOffset + alloc->allocationSize;
        REP_DEBUG("[" << alloc->memoryChunkOffset << "] " << alloc->allocationSize << " bytes allocated (#" << alloc->id
                      << ")",
                  LogChannelBitsFlag::DEFAULT)
        if (alloc->pNext != nullptr)
        {
            memoryAlloc_t *next_alloc = alloc->pNext;
            uint64_t gap = next_alloc->memoryChunkOffset - position;
            if (gap != 0)
            {
                REP_DEBUG("[" << alloc->memoryChunkOffset + alloc->allocationSize << "] " << gap << " bytes free",
                          LogChannelBitsFlag::DEFAULT)
            }
        }
        else
        {
            uint64_t lastGap = memoryPool[0].size - position;
            REP_DEBUG("[" << alloc->memoryChunkOffset + alloc->allocationSize << "] " << lastGap << " bytes free",
                      LogChannelBitsFlag::DEFAULT)
        }
        alloc = alloc->pNext;
    }
    REP_DEBUG("DUMP MEMORY CHUNK 0", LogChannelBitsFlag::DEFAULT)
    REP_DEBUG("##################################", LogChannelBitsFlag::DEFAULT)
}

VkBuffer VulkanMemoryManager::getBuffer(memoryAllocId allocId)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    int chunk = 0;
    VkBuffer buffer = VK_NULL_HANDLE;

    while (chunk < poolSize && buffer == VK_NULL_HANDLE)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && buffer == VK_NULL_HANDLE)
        {
            if (alloc->id == allocId)
            {
                buffer = alloc->buffer;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }

    if (buffer == VK_NULL_HANDLE)
    {
        throw std::runtime_error("unable to find memory with id " + allocId);
    }
    return buffer;
}


void
VulkanMemoryManager::getMemoryAllocation(memoryAllocId allocId, memoryAlloc_t **memoryAlloc, VkDeviceMemory *memory)
{
    vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
    bool found = false;
    int chunk = 0;

    while (chunk < poolSize && !found)
    {
        memoryAlloc_t *alloc = allocations[chunk];
        while (alloc != nullptr && !found)
        {
            if (alloc->id == allocId)
            {
                found = true;
                *memoryAlloc = alloc;
                *memory = memoryPool[chunk].memory;
            }
            alloc = alloc->pNext;
        }
        chunk++;
    }

    if (!found)
    {
        throw std::runtime_error("unable to find memory with id " + allocId);
    }
}


}
}
}