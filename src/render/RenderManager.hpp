#ifndef RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
#define RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"
#include "../common/vulkan/vulkan_helpers.hpp"

namespace rep
{


struct RenderManagerInitializeArgs_t
{
    uint32_t validationLayerCount;
    const char **ppValidationLayersCount;
    uint32_t deviceExtensionCount;
    const char **ppDeviceExtensions;
};


class RenderManager :
        public SingletonManager<RenderManager, RenderManagerInitializeArgs_t>
{
    friend SingletonManager<RenderManager, RenderManagerInitializeArgs_t>;

private:
    /**
     * Synchronisation related members
     */
    const int MAX_CONCURRENT_FRAMES = 2;
    size_t currentFrame = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFligtFences;

    /**
     * instance and device related members
     */
    VkInstance vulkanInstance;
    VkDebugReportCallbackEXT debugReportCallback;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkQueue graphicQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    /**
     *  swapchain related member
     */
    VkSwapchainKHR swapchain;
    VkExtent2D swapchainExtent;
    VkFormat swapchainImageFormat;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    /**
     * graphic chain related members
     */
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;

    /**
     * depth test related members
     */
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;


    std::vector<PipelineInfos> availablePipelines;

protected:
    RenderManager() = default;

    RenderManager(const RenderManager &) = delete;

    RenderManager &operator=(const RenderManager &) = delete;

    void vInit(RenderManagerInitializeArgs_t args) override;

    void vDestroy() override;

    void destroySwapchain();

    void updateSwapchain();

    void createSwapchain();

    void createDefaultGraphicPipeline(const char *vertShaderFilename,
                                      const char *fragShaderFilename);

    void createFramebuffers();

    void createDepthTest();

    void createCommandBuffers();

    void createAsyncObjects();

    void destroyAsyncObjects();

public:
    void vUpdate() override;

};

}


#endif //RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
