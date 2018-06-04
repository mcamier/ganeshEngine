#ifndef RENDERENGINEPLAYGROUND_VULKANFUNCTIONS_HPP
#define RENDERENGINEPLAYGROUND_VULKANFUNCTIONS_HPP

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace rep
{

#define EXPORTED_VULKAN_FUNCTION(function)                                  \
    extern PFN_##function function;

#define GLOBAL_LEVEL_VULKAN_FUNCTION(function)                              \
    extern PFN_##function function;

#define INSTANCE_LEVEL_VULKAN_FUNCTION(function)                            \
    extern PFN_##function function;

#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)  \
    extern PFN_##function function;

#define DEVICE_LEVEL_VULKAN_FUNCTION(function)                              \
    extern PFN_##function function;

#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)    \
    extern PFN_##function function;


#include "listVulkanFunctions.inc.hpp"

}

#endif
