#ifndef RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
#define RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"
#include "vulkan_helpers.hpp"
#include "geometry.hpp"

namespace rep
{

// Stores values required for the VulkanContextManager's initialization
struct VulkanContextManagerInitializeArgs_t
{
    uint32_t validationLayerCount;
    const char **ppValidationLayersCount;
    uint32_t deviceExtensionCount;
    const char **ppDeviceExtensions;
    bool validationLayerEnabled;
};


// Manager responsible of the preparation and the destruction of a vulkan context:
//  vulkan instance creation
//  physical device selection
//  logical device creation
//  swapchain creation
//  framebuffer for rendering creation
//  depth test creation
//  presentation queue and graphics queue creation
//  a graphics command pool creation
class VulkanContextManager :
        public SingletonManager<VulkanContextManager, VulkanContextManagerInitializeArgs_t>
{
    friend SingletonManager<VulkanContextManager, VulkanContextManagerInitializeArgs_t>;

private:
    // Synchronisation related members
    const int MAX_CONCURRENT_FRAMES = 2;
    size_t currentFrame = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFligtFences;
    // instance and device related members
    VkInstance vulkanInstance;
    VkDebugReportCallbackEXT debugReportCallback;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkQueue graphicQueue;
    VkQueue presentQueue;
    VkCommandPool graphicCommandPool;
    // swapchain related member
    VkSwapchainKHR swapchain;
    VkExtent2D swapchainExtent;
    VkFormat swapchainImageFormat;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    // depth test related members
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    // graphic chain related members
    VkRenderPass renderPass;


protected:
    VulkanContextManager() = default;

    VulkanContextManager(const VulkanContextManager &) = delete;

    VulkanContextManager &operator=(const VulkanContextManager &) = delete;

    void vInit(VulkanContextManagerInitializeArgs_t args) override;

    void vDestroy() override;

    void initVulkanInstance(VulkanContextManagerInitializeArgs_t args);

    void destroyVulkanInstance();

    void initSwapchain();

    void updateSwapchain();

    void destroySwapchain();

    void initFramebuffers();

    void destroyFramebuffers();

    void initDepthTest();

    void destroyDepthTest();

    void initAsyncObjects();

    void destroyAsyncObjects();

public:
    void vUpdate() override;

    vulkanContextInfos_t getContextInfos();

    VkExtent2D getCurrentExtent();

    VkImageView getSwapchainImageView(uint32_t acquiredImage);
};


// memoryChunk_t Describes a memory chunk allocated and managed by the VulkanMemoryManager in order to provide fastest
// "sub allocations"
struct memoryChunk_t
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    uint64_t size;

};


typedef uint64_t memoryAllocId;


// memoryAlloc_t describes a memory block which belongs to a memory chunk managed by VulkanMemoryManager, it has
// virtually no allocation time
struct memoryAlloc_t
{
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

    memoryAlloc_t()
    {
        id = lastId++;
        memoryChunkIndex = -1;
        memoryChunkOffset = -1;
        allocationSize = -1;
        alignmentOffset = 0;
        buffer = VK_NULL_HANDLE;
        pPrevious = nullptr;
        pNext = nullptr;
    }

    // compute the position of the end of the current memory block
    VkDeviceSize getEndPosition() const
    {
        return memoryChunkOffset + alignmentOffset + allocationSize;
    }

    VkDeviceSize getAlignedBeginPosition() const
    {
        return memoryChunkOffset + alignmentOffset;
    }

    VkDeviceSize getDataSize() const
    {
        return alignmentOffset + allocationSize;
    }
};


//
// Stores values required for the VulkanContextManager's initialization
struct VulkanMemoryManagerInitializeArgs_t
{
    uint64_t chunkSize;
    uint32_t poolSize;
};


//
//
class UniformAllocatorPolicy
{
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
class BufferAllocatorPolicy
{
private:
    BufferAllocatorPolicy() = default;

    ~BufferAllocatorPolicy() = default;

public:
    BufferAllocatorPolicy(const BufferAllocatorPolicy &) = delete;

    BufferAllocatorPolicy &operator=(const BufferAllocatorPolicy &) = delete;

    static VkDeviceSize getAlignmentRequirement(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer);

    static VkBuffer createBuffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage);
};


// Responsible of managing eagerly allocated memory chunks for vulkan resources in order to avoid multiple
// vkDeviceMemory creation
class VulkanMemoryManager :
        public SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t>
{
    friend SingletonManager<VulkanMemoryManager, VulkanMemoryManagerInitializeArgs_t>;

private:
    // Amount of memory chunk allocated during initialization
    uint64_t chunkSize;
    // Size of a single memory chunk
    uint32_t poolSize;
    // store informations about each memory chunk available in the pool
    std::vector<memoryChunk_t> memoryPool;
    // Store collection of first node of linked list of type memoryAlloc_t
    // the collection is the same size as the amount of memory chunk
    std::vector<memoryAlloc_t *> allocations;

protected:
    VulkanMemoryManager() = default;

    VulkanMemoryManager(const VulkanMemoryManager &) = delete;

    VulkanMemoryManager &operator=(const VulkanMemoryManager &) = delete;

    void vInit(VulkanMemoryManagerInitializeArgs_t args) override;

    void vDestroy() override;

public:
    void vUpdate() override
    {}

    // This method will search into its memory pool a place to sub allocate memory for the required size
    // No device memory allocation occurs during this call, a new buffer is created and bound to a specific
    // memory location (memory allocation occurs during initialization of the manager)
    memoryAllocId allocateBuffer(uint64_t size, VkBufferUsageFlags usage);

    // Is like the non templated version of the method allocateBuffer, except this one will copy the provided datas
    // into the buffer
    template<typename... Args>
    memoryAllocId allocateBuffer(uint64_t size, VkBufferUsageFlags usage, void* ptr, uint64_t dataSize, Args... args)
    {
        memoryAllocId allocId = this->allocateWithPolicy<BufferAllocatorPolicy>(size, usage);
        fill(allocId, ptr, dataSize, args...);

        return allocId;
    }

    memoryAllocId allocateUniform(uint64_t size);

    // Release a given sub allocation, it's release its bound buffer and make the space previously available for
    // later allocation request
    void free(memoryAllocId allocId);

    VkBuffer getBuffer(memoryAllocId allocId);

    template<typename... Args>
    void fill(memoryAllocId allocId, void *ptr, uint64_t size, Args... args)
    {

        memoryAlloc_t *memoryAlloc = nullptr;
        VkDeviceMemory memory;
        getMemoryAllocation(allocId, &memoryAlloc, &memory);
        uint64_t memOffset = memoryAlloc->memoryChunkOffset + memoryAlloc->alignmentOffset;

        uint64_t requiredSize = sumSize(ptr, size, args...);
        if (requiredSize > memoryAlloc->getDataSize())
        {
            REP_FATAL("memory allocation is too small", LogChannelBitsFlag::DEFAULT)
        }

        fillWithOffset<Args...>(allocId, memOffset, ptr, size, args...);
    }

private:
    // Allocate memory within the vulkanMemoryManager with a specific allocator
    template<typename allocator>
    memoryAllocId allocateWithPolicy(uint64_t size, VkBufferUsageFlags usage)
    {
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        VkBuffer buffer = allocator::createBuffer(ctxt.device, size, usage);
        VkDeviceSize alignment = allocator::getAlignmentRequirement(ctxt.device, ctxt.physicalDevice, buffer);

        return findAvailableMemory(size, alignment, buffer);
    }

    template<typename... Args>
    void fillWithOffset(memoryAllocId allocId, uint64_t offset, void *ptr, uint64_t size, Args... args)
    {
        void *pLocalMem;
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        memoryAlloc_t *memoryAlloc = nullptr;
        VkDeviceMemory memory;
        getMemoryAllocation(allocId, &memoryAlloc, &memory);

        vkMapMemory(ctxt.device, memory, offset, size, 0, &pLocalMem);
        memcpy(pLocalMem, ptr, size);
        vkUnmapMemory(ctxt.device, memory);

        uint64_t nextOffset = offset + size;

        // recursive call of the method until paramater pack is not empty
        fillWithOffset(allocId, nextOffset, args...);
    }

    template<>
    void fillWithOffset(memoryAllocId allocId, uint64_t offset, void *ptr, uint64_t size)
    {
        void *pLocalMem;
        vulkanContextInfos_t ctxt = VulkanContextManager::get().getContextInfos();
        memoryAlloc_t *memoryAlloc = nullptr;
        VkDeviceMemory memory;
        getMemoryAllocation(allocId, &memoryAlloc, &memory);

        vkMapMemory(ctxt.device, memory, offset, size, 0, &pLocalMem);
        memcpy(pLocalMem, ptr, size);
        vkUnmapMemory(ctxt.device, memory);
    }

    // sum up the provided data's size in the parameter pack
    template<typename... Args>
    uint64_t sumSize(void *ptr, uint64_t size, Args... args)
    {
        return size + sumSize(args...);
    }

    // end call for the recursion of the parameter pack for the sum up
    template<>
    uint64_t sumSize(void *ptr, uint64_t size)
    {
        return size;
    }

    void getMemoryAllocation(memoryAllocId allocId, memoryAlloc_t **memoryAlloc, VkDeviceMemory *memory);

    memoryAllocId findAvailableMemory(VkDeviceSize size, VkDeviceSize alignment, VkBuffer &buffer);

    // display the memory status in the log
    void dump();
};

}

#endif //RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
