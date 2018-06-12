#ifndef RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
#define RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"
#include "vulkan_helpers.hpp"
#include "geometry.hpp"

namespace rep
{

/**
 * Stores values required for the VulkanContextManager's initialization
 */
struct VulkanContextManagerInitializeArgs_t
{
    uint32_t            validationLayerCount;
    const char**        ppValidationLayersCount;
    uint32_t            deviceExtensionCount;
    const char**        ppDeviceExtensions;
    bool                validationLayerEnabled;
};


/**
 * Manager responsible of the preparation and the destruction of a vulkan context:
 *  vulkan instance creation
 *  physical device selection
 *  logical device creation
 *  swapchain creation
 *  framebuffer for rendering creation
 *  depth test creation
 *  presentation queue and graphics queue creation
 *  a graphics command pool creation
 */
class VulkanContextManager :
        public SingletonManager<VulkanContextManager, VulkanContextManagerInitializeArgs_t>
{
    friend SingletonManager<VulkanContextManager, VulkanContextManagerInitializeArgs_t>;

private:
    /**
     * Synchronisation related members
     */
    const int                       MAX_CONCURRENT_FRAMES = 2;
    size_t                          currentFrame = 0;
    std::vector<VkSemaphore>        imageAvailableSemaphores;
    std::vector<VkSemaphore>        renderFinishedSemaphores;
    std::vector<VkFence>            inFligtFences;
    /**
     * instance and device related members
     */
    VkInstance                      vulkanInstance;
    VkDebugReportCallbackEXT        debugReportCallback;
    VkSurfaceKHR                    surface;
    VkPhysicalDevice                physicalDevice;
    VkDevice                        device;

    VkQueue                         graphicQueue;
    VkQueue                         presentQueue;
    VkCommandPool                   graphicCommandPool;
    /**
     *  swapchain related member
     */
    VkSwapchainKHR                  swapchain;
    VkExtent2D                      swapchainExtent;
    VkFormat                        swapchainImageFormat;
    std::vector<VkImage>            swapchainImages;
    std::vector<VkImageView>        swapchainImageViews;
    std::vector<VkFramebuffer>      swapChainFramebuffers;
    /**
     * depth test related members
     */
    VkImage                         depthImage;
    VkDeviceMemory                  depthImageMemory;
    VkImageView                     depthImageView;
    /**
     * graphic chain related members
     */
    VkRenderPass                    renderPass;


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

}

#endif //RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
