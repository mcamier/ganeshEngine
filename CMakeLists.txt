cmake_minimum_required(VERSION 3.3)
project(ganeshEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ganeshEngine_SOURCE_DIR}/cmake")

add_definitions(-DDEBUG_ASSERTION_ENABLED)
add_definitions(-DENABLE_PROFILING)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif(WIN32)

add_subdirectory(ganeshEngineCore)
add_subdirectory(ganeshEngineDemo)
