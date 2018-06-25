#ifndef GE_RENDERMANAGER_HPP
#define GE_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"
#include "helper.hpp"
#include "geometry.hpp"

namespace ge
{
namespace vulkan
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
    const int                   MAX_CONCURRENT_FRAMES = 2;
    size_t                      currentFrame = 0;
    std::vector<VkSemaphore>    imageAvailableSemaphores;
    std::vector<VkSemaphore>    renderFinishedSemaphores;
    std::vector<VkFence>        inFligtFences;

    // instance and device related members
    VkInstance                  vulkanInstance          = VK_NULL_HANDLE;
    VkDebugReportCallbackEXT    debugReportCallback     = VK_NULL_HANDLE;
    VkSurfaceKHR                surface                 = VK_NULL_HANDLE;
    VkPhysicalDevice            physicalDevice          = VK_NULL_HANDLE;
    VkDevice                    device                  = VK_NULL_HANDLE;

    VkQueue                     graphicQueue            = VK_NULL_HANDLE;
    VkQueue                     presentQueue            = VK_NULL_HANDLE;
    VkCommandPool               graphicCommandPool      = VK_NULL_HANDLE;

    // swapchain related member
    VkSwapchainKHR              swapchain               = VK_NULL_HANDLE;
    VkExtent2D                  swapchainExtent         = {};
    VkFormat                    swapchainImageFormat    = {};
    std::vector<VkImage>        swapchainImages;
    std::vector<VkImageView>    swapchainImageViews;
    std::vector<VkFramebuffer>  swapChainFramebuffers;

    // depth test related members
    VkImage                     depthImage              = VK_NULL_HANDLE;
    VkDeviceMemory              depthImageMemory        = VK_NULL_HANDLE;
    VkImageView                 depthImageView          = VK_NULL_HANDLE;

    // graphic chain related members
    VkRenderPass                renderPass              = VK_NULL_HANDLE;


protected:
    VulkanContextManager() = default;

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
    VulkanContextManager(const VulkanContextManager &) = delete;

    VulkanContextManager &operator=(const VulkanContextManager &) = delete;

    void vUpdate() override;

    vulkanContextInfos_t getContextInfos();

    VkExtent2D getCurrentExtent();

    VkImageView getSwapchainImageView(uint32_t acquiredImage);
};

}
}

#endif //GE_RENDERMANAGER_HPP
