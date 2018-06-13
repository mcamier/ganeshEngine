#ifndef RENDERENGINEPLAYGROUND_HELPERS_HPP
#define RENDERENGINEPLAYGROUND_HELPERS_HPP

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include "../common/logger.hpp"
#include "geometry.hpp"
#include "pipeline.hpp"

namespace rep
{

struct QueueFamilyIndices
{
    uint32_t graphicsFamily = static_cast<uint32_t>(-1);
    uint32_t presentFamily = static_cast<uint32_t>(-1);

    bool isComplete()
    {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};


struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};



template<typename VERTEX>
void loadModel(std::string &modelPath,
               std::vector<VERTEX> &vertices,
               std::vector<uint32_t> &indices);


std::vector<const char *> getRequiredExtensions();


bool isValidationLayerSupported(uint16_t validationLayerCount,
                                const char **ppValidationLayers);


void createSurface(VkInstance &vulkanInstance,
                   GLFWwindow *window,
                   VkSurfaceKHR *surface);


void pickPhysicalDevice(VkInstance const &vulkanInstance,
                        VkSurfaceKHR surface,
                        uint16_t countRequiredExtension,
                        const char **ppDeviceExtensions,
                        VkPhysicalDevice *physicalDevice);


bool isPhysicalDeviceSuitable(VkPhysicalDevice device,
                              VkSurfaceKHR surface,
                              uint16_t countRequiredExtension,
                              const char **ppDeviceExtensions);


bool checkDeviceExtensionSupport(VkPhysicalDevice device,
                                 uint16_t requiredExtensionCount,
                                 const char **ppRequiredExtensions);


QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface);


SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,
                                              VkSurfaceKHR surface);

void createLogicalDevice(VkPhysicalDevice physicalDevice,
                         QueueFamilyIndices indices,
                         uint32_t validationLayerCount,
                         const char **validationLayers,
                         uint32_t deviceExtensionCount,
                         const char **deviceExtensions,
                         VkDevice *device);


void createCommandPool(VkPhysicalDevice physicalDevice,
                       VkDevice device,
                       uint32_t queueIndex,
                       VkCommandPool *commandPool);


void createDescriptorPool(VkDevice device,
                          VkDescriptorPool *descriptorPool);


VkFormat findSupportedFormat(VkPhysicalDevice physicalDevice,
                             const std::vector<VkFormat> &candidates,
                             VkImageTiling tiling,
                             VkFormatFeatureFlags features);


VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);


bool hasStencilComponent(VkFormat format);


uint32_t findMemoryType(VkPhysicalDevice physicalDevice,
                        uint32_t typeFilter,
                        VkMemoryPropertyFlags properties);


void createBuffer(VkDevice device,
                  VkPhysicalDevice physicalDevice,
                  VkDeviceSize size,
                  VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties,
                  VkBuffer &buffer,
                  VkDeviceMemory &bufferMemory);


VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);


VkPresentModeKHR chooseSwapPresentationMode(const std::vector<VkPresentModeKHR> &availableModes);


VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,
                            uint32_t defaultWidth,
                            uint32_t defaultHeight);


VkImageView createImageView(VkDevice device,
                            VkImage image,
                            VkFormat format,
                            VkImageAspectFlags aspectFlags);


void createImage(VkDevice device,
                 VkPhysicalDevice,
                 uint32_t width,
                 uint32_t height,
                 VkFormat format,
                 VkImageTiling tiling,
                 VkImageUsageFlags usages,
                 VkImage &image,
                 VkDeviceMemory &deviceMemory);


void createRenderPass(VkPhysicalDevice physicalDevice,
                      VkDevice device,
                      VkFormat swapchainImageFormat,
                      VkRenderPass *renderPass);


void createShaderModule(VkDevice device,
                        const std::vector<char> &code,
                        VkShaderModule *shaderModule);


VkCommandBuffer beginSingleTimeCommand(VkDevice device,
                                       VkCommandPool commandPool);


void endSingleTimeCommand(VkDevice device,
                          VkCommandPool commandPool,
                          VkCommandBuffer commandBuffer,
                          VkQueue queueToSubmit);


void transitionImageLayout(VkDevice device,
                           VkCommandPool commandPool,
                           VkQueue queue,
                           VkImage image,
                           VkFormat format,
                           VkImageLayout oldLayout,
                           VkImageLayout newLayout);


void populateDeviceMemory(VkDevice device,
                          VkDeviceMemory deviceMemory,
                          uint32_t offset,
                          uint32_t size,
                          void *pSrc);

void copyBuffer(VkDevice device,
                VkCommandPool commandPool,
                VkQueue queueToSubmit,
                VkBuffer sourceBuffer,
                VkBuffer destinationBuffer,
                uint64_t size);


/*
 * Debug callback report utils
 */
VkResult createDebugReportCallbackEXT(VkInstance instance,
                                      const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugReportCallbackEXT *pCallback);


void destroyDebugReportCallbackEXT(VkInstance instance,
                                   VkDebugReportCallbackEXT callback,
                                   const VkAllocationCallbacks *pAllocator);


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
                                                    VkDebugReportObjectTypeEXT objType,
                                                    uint64_t obj,
                                                    size_t location,
                                                    int32_t code,
                                                    const char *layerPrefix,
                                                    const char *msg,
                                                    void *userData)
{
    REP_ERROR(msg, LogChannelBitsFlag::RENDER)
    /**
     * We do want to loose log entries if vulkan crash the application after this error
     */
    LoggerManager::get().flush();
    return VK_FALSE;
}

}


/*
#ifdef _WIN32

    #include <Windows.h>

    #define LIBRARY_TYPE HMODULE
    #define LoadFunction GetProcAddress
#elif defined __linux
    #include <dlfcn.h>
    #define LIBRARY_TYPE void*
    #define LoadFunction dlsym
#endif

namespace rep
{


    void getVulkanLibHandler(LIBRARY_TYPE &vulkan_library)
    {
#ifdef _WIN32
        vulkan_library = LoadLibrary("vulkan-1.dll");
#elif defined __linux
        vulkan_library = dlopen("vulkan-1.so.1");
#endif

        if (nullptr == vulkan_library)
        {
            throw std::runtime_error("failed to get handler on vulkan dynamic library");
        }
    }

    void bindVulkanPointertoFunctions(LIBRARY_TYPE const &vulkan_library)
    {
#define EXPORTED_VULKAN_FUNCTION(function)\
    function = (PFN_##function) LoadFunction(vulkan_library, #function);\
    if((function) == nullptr){\
        throw std::runtime_error("failed to load vulkan function pointer");\
    }

#define GLOBAL_LEVEL_VULKAN_FUNCTION(function) \
    function = (PFN_##function) vkGetInstanceProcAddr(nullptr, #function);\
    if((function) == nullptr){\
        throw std::runtime_error("failed to load vulkan function pointer");\
    }

#define INSTANCE_LEVEL_VULKAN_FUNCTION(function)
#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)
#define DEVICE_LEVEL_VULKAN_FUNCTION(function)
#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)

#include "render/listVulkanFunctions.inc.hpp"
    }
}
*/

#endif
