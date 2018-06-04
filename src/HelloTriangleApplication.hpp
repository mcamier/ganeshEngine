#ifndef RENDERENGINEPLAYGROUND_HELLOTRIANGLEAPPLICATION_H
#define RENDERENGINEPLAYGROUND_HELLOTRIANGLEAPPLICATION_H

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>

#include "utils.hpp"

const int MAX_CONCURRENT_FRAMES = 2;

//https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html#introduction

class HelloTriangleApplication
{

private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::string MODEL_PATH = "../models/chalet.obj";
    const std::string TEXTURE_PATH = "../textures/chalet.jpg";

    std::vector<VertexPosColorTex> vertices;
    std::vector<uint32_t> indices;

#ifdef _DEBUG
    const std::vector<const char *> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
    };
#endif

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    GLFWwindow *pWindow;

    VkInstance vulkanInstance;
    VkDebugReportCallbackEXT callback;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicQueue;
    VkQueue presentationQueue;

    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkExtent2D swapChainExtent;
    VkFormat swapChainImageFormat;

    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;

    VkCommandPool commandPool;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer uboBuffer;
    VkDeviceMemory uboBufferMemory;
    VkImage textureImage;
    VkImageView textureImageView;
    VkImageView textureSampler;
    VkDeviceMemory textureImageMemory;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    std::vector<VkCommandBuffer> commandBuffers;

    size_t currentFrame = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFligtFences;

public:
    void run();

private:
    void initWindow(); //ok

    void initVulkan(); //ok

    void mainLoop(); //ok

    void drawFrame();

    void cleanup();

    void cleanupSwapchain();

    void createInstance();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSurface();

    void createSwapChain();

    void recreateSwapChain();

    void createImageViews();

    void createRenderPass();

    void createGraphicPipeline();

    void createFramebuffers();

    void createCommandPool();

    void createCommandBuffers();

    void createOrchestratorObjects();

    void createVertexBuffer();

    void createIndexBuffer();

    void createUboBuffer();

    void createDescriptorSetLayout();

    void createDescriptorpool();

    void createDescriptorSet();

    void updateUniformBuffer();

    void createTextureImage();

    void createTextureImageView();

    void createTextureSampler();

    void createDepthResources();

    VkImageView createImageView(VkImage image,
                                VkFormat format,
                                VkImageAspectFlags aspectFlags);

    VkShaderModule createShaderModule(const std::vector<char> &code);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentationMode(const std::vector<VkPresentModeKHR> &availableModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    std::vector<const char *> getRequiredExtensions();

    void loadModel();

#ifdef _DEBUG

    bool checkValidationLayerSupport();

    void setupVulkanCallback();

#endif
};


#endif //RENDERENGINEPLAYGROUND_HELLOTRIANGLEAPPLICATION_H
