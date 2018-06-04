#include "vulkanFunctions.hpp"

namespace rep
{

#define EXPORTED_VULKAN_FUNCTION(function)                                  \
    PFN_##function function;

#define GLOBAL_LEVEL_VULKAN_FUNCTION(function)                              \
    PFN_##function function;

#define INSTANCE_LEVEL_VULKAN_FUNCTION(function)                            \
    PFN_##function function;

#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)  \
    PFN_##function function;

#define DEVICE_LEVEL_VULKAN_FUNCTION(function)                              \
    PFN_##function function;

#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION(function, extension)    \
    PFN_##function function;


#include "listVulkanFunctions.inc.hpp"

}