cmake_minimum_required(VERSION 3.10)
project(ganeshEngine VERSION 1.0.0 LANGUAGES CXX)

########################################################################################################################
# dependencies
find_package(Vulkan REQUIRED)
add_subdirectory(libs/glfw)
add_subdirectory (libs/glm)
add_subdirectory (libs/tinyobjloader)
include_directories(${VULKAN_INCLUDE_DIR})

########################################################################################################################
# targets
add_executable(GEDemo
        src/main.cpp
        src/Application.cpp
        src/Application.hpp
        src/window/manager.cpp
        src/window/manager.hpp
        src/input/inputManager.cpp
        src/input/inputManager.hpp
        src/input/input_glfw.hpp
        src/input/input.hpp
        src/vulkan/manager.cpp
        src/vulkan/manager.hpp
        src/vulkan/memory/common.hpp
        src/vulkan/memory/common.cpp
        src/vulkan/memory/manager.cpp
        src/vulkan/memory/manager.hpp
        src/vulkan/helper.cpp
        src/vulkan/helper.hpp
        src/vulkan/geometry.cpp
        src/vulkan/geometry.hpp
        src/vulkan/pipeline/pipeline.cpp
        src/vulkan/pipeline/pipeline.hpp
        src/vulkan/initializers.cpp
        src/vulkan/initializers.hpp
        src/common/managers.hpp
        src/common/common.cpp
        src/common/common.hpp
        src/common/logger.cpp
        src/common/logger.hpp
        src/common/memory.cpp
        src/common/memory.hpp
        src/common/log_utils.hpp
        src/common/clock.cpp
        src/common/clock.hpp
        src/common/profiler.cpp
        src/common/profiler.hpp)

########################################################################################################################
# GEDemo target's proerties
target_include_directories(GEDemo
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(GEDemo PRIVATE -Werror)
target_compile_features(GEDemo PRIVATE cxx_std_14)

target_link_libraries(GEDemo
    PUBLIC
        ${Vulkan_LIBRARY}
        glm
        tinyobjloader
        glfw)