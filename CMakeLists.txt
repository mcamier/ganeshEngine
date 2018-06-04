cmake_minimum_required(VERSION 3.10)
project(renderEnginePlayground)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DLOGGING_ENABLED
        -DPROFILING_ENABLED)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -lstdc++ -lpthread")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #activate folder's creation for visual studio project generation


find_package(vulkan REQUIRED)
find_package(GLFW REQUIRED)

add_subdirectory(libs)

include_directories(
        C:/VulkanSDK/1.1.73.0/Include
        ./libs/glm
        ./libs/stb
        ./libs/tinyobjloader
        ./libs/glfw/include)

set(LIBRARIES
        ${GLFW_glfw_LIBRARY}
        ${Vulkan_LIBRARY})

add_executable(renderEnginePlayground
        src/main.cpp
        src/render/listVulkanFunctions.inc.hpp
        src/HelloTriangleApplication.cpp
        src/HelloTriangleApplication.hpp
        src/utils.cpp
        src/utils.hpp
        src/render/vulkanFunctions.cpp
        src/render/vulkanFunctions.hpp
        src/Application.cpp
        src/Application.hpp
        src/render/RenderManager.cpp
        src/render/RenderManager.hpp
        src/window/WindowManager.cpp
        src/window/WindowManager.hpp
        src/common/vulkan/vulkan_instances.cpp
        src/common/vulkan/vulkan_helpers.hpp
        src/common/managers.hpp
        src/common/common.cpp
        src/common/common.hpp
        src/common/logger.cpp
        src/common/logger.hpp
        src/common/memory.cpp
        src/common/memory.hpp
        src/common/log_utils.cpp
        src/common/log_utils.hpp
        src/common/clock.cpp
        src/common/clock.hpp
        src/common/profiler.cpp
        src/common/profiler.hpp)
target_link_libraries(renderEnginePlayground ${LIBRARIES})
