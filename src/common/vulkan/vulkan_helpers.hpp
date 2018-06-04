#ifndef RENDERENGINEPLAYGROUND_HELPERS_HPP
#define RENDERENGINEPLAYGROUND_HELPERS_HPP

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include "../logger.hpp"

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


std::vector<const char *> getRequiredExtensions();


bool isValidationLayerSupported(uint16_t validationLayerCount,
                                const char ** ppValidationLayers);


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
                              const char** ppDeviceExtensions);


bool checkDeviceExtensionSupport(VkPhysicalDevice device,
                                 uint16_t requiredExtensionCount,
                                 const char** ppRequiredExtensions);


QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR surface);


SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,
                                              VkSurfaceKHR surface);

void createLogicalDevice(VkPhysicalDevice physicalDevice,
                         QueueFamilyIndices indices,
                         uint32_t validationLayerCount,
                         const char** validationLayers,
                         uint32_t deviceExtensionCount,
                         const char** deviceExtensions,
                         VkDevice *device);


void createCommandPool(VkPhysicalDevice physicalDevice,
                       VkDevice device,
                       QueueFamilyIndices indices,
                       VkCommandPool *commandPool);


VkFormat findSupportedFormat(VkPhysicalDevice physicalDevice,
                             const std::vector<VkFormat> &candidates,
                             VkImageTiling tiling, VkFormatFeatureFlags features);


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
    REP_WARNING(msg, LOG_CHANNEL::RENDER)
    return VK_FALSE;
}

}

#endif
