#ifndef RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
#define RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "../common/managers.hpp"

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
        public Manager<RenderManager, RenderManagerInitializeArgs_t>
{
    friend Manager<RenderManager, RenderManagerInitializeArgs_t>;

private:
    VkInstance vulkanInstance;
    VkDebugReportCallbackEXT debugReportCallback;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool;

protected:
    RenderManager() = default;

    RenderManager(const RenderManager &) = delete;

    RenderManager &operator=(const RenderManager &) = delete;

    void vInit(RenderManagerInitializeArgs_t args) override;

    void vDestroy() override;

public:
    void vUpdate() override;
};

}


#endif //RENDERENGINEPLAYGROUND_RENDERMANAGER_HPP
