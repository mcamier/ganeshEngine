cmake_minimum_required(VERSION 3.2.3)
project(ganeshEngine C CXX)

option(BUILD_DOC "Build ganeshEngine documentation" ON)
option(WITH_GLFW "Include GLFW as window wrapper" ON)
option(WITH_RENDER_API_GL "Include OpenGL Rendering API" ON)
option(WITH_RENDER_API_VULKAN "Include Vulkan Rendering API" OFF)

#activate folder's creation for visual studio project generation
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_definitions(
    -DDEBUG_ASSERTION_ENABLED
    -DPROFILING_ENABLED
    -DLOGGING_ENABLED
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS)

#find_package(OpenGL REQUIRED)
include(libs.cmake)

if(BUILD_DOC)
    set(DOC_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/doc/${PROJECT_NAME}" CACHE PATH "Path to the documentation")
    include(doc.cmake)
endif()

add_subdirectory(ghCore)
add_subdirectory(ghGlfwAPI)
add_subdirectory(ghRenderOpenglAPI)
add_subdirectory(ghRenderVulkanAPI)
add_subdirectory(ghEngine)

#add_subdirectory(demo)
#add_subdirectory(test)