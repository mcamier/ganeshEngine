#ifndef GE_HELPERS_HPP
#define GE_HELPERS_HPP

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include "../common/logger.hpp"
#include "geometry.hpp"
#include "pipeline/pipeline.hpp"

using ge::utils::LoggerManager;

namespace ge {
namespace vulkan {
namespace helper {

struct QueueFamilyIndices {
    uint32_t graphicsFamily = std::numeric_limits<uint32_t>::max();
    uint32_t presentFamily = std::numeric_limits<uint32_t>::max();

    bool isComplete() {
        return graphicsFamily != std::numeric_limits<uint32_t>::max() &&
               presentFamily != std::numeric_limits<uint32_t>::max();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

template<typename VERTEX>
void loadModel(std::string &modelPath, std::vector<VERTEX> &vertices, std::vector<uint32_t> &indices);

std::vector<const char *> getRequiredExtensions();

bool isValidationLayerSupported(uint16_t validationLayerCount, const char **ppValidationLayers);

void createSurface(VkInstance &vulkanInstance, GLFWwindow *window, VkSurfaceKHR *surface);

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

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

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

void createDescriptorPool(VkDevice device, VkDescriptorPool *descriptorPool);

VkFormat findSupportedFormat(VkPhysicalDevice physicalDevice,
                             const std::vector<VkFormat> &candidates,
                             VkImageTiling tiling,
                             VkFormatFeatureFlags features);

VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);

bool hasStencilComponent(VkFormat format);

uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

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

void createShaderModule(VkDevice device, const std::vector<char> &code, VkShaderModule *shaderModule);

VkCommandBuffer beginSingleTimeCommand(VkDevice device, VkCommandPool commandPool);

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

// Debug callback report utils
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
                                                    void *userData) {
    REP_ERROR(msg, ge::utils::LogChannelBitsFlag::RENDER)
    //We do want to loose log entries if vulkan crash the application after this error
    LoggerManager::get().flush();
    return VK_FALSE;
}

} // namespace helper
} // namespace vulkan
} // namespace ge

#endif
