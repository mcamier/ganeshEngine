#ifndef RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
#define RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"
#include "../common/vulkan/vulkan_helpers.hpp"
#include "geometry.hpp"

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
    const char * DEFAULT_VERT_SHADER_LOCATION = "C:/Users/Mickael/Documents/workspace/renderEnginePlayground/shaders/compiled/vert.spv";
    const char * DEFAULT_FRAG_SHADER_LOCATION = "C:/Users/Mickael/Documents/workspace/renderEnginePlayground/shaders/compiled/frag.spv";
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
    VkCommandPool graphicCommandPool;
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
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;

    /**
     * depth test related members
     */
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;


    std::vector<pipelineInfos_t> availablePipelines;
    std::vector<meshInstance_t> registeredMeshes;
    bool registeredMeshVectorUpdated = false;

    VkBuffer vertexAndIndexBuffer;
    VkDeviceMemory vertexAndIndexBufferMemory;

    /**
     * temp
     */
    std::vector<VertexPosColorTex> vertices;
    std::vector<uint32_t> indices;

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

    void destroyDepthTest();

    void createCommandBuffers();

    void createAsyncObjects();

    void destroyAsyncObjects();

public:
    void vUpdate() override;

    void createVertexAndIndexBuffer();

};

}

#endif //RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
