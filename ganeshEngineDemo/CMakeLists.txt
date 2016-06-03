project(ganeshEngineDemo)
set(ExeName Demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(DemoInclude
    "Include"
    "../ganeshEngineCore/Include")
include_directories (${DemoInclude})

set(SOURCE_FILES
    "Source/main.cpp")

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

if(WIN32)
    add_executable(${ExeName} WIN32 ${SOURCE_FILES})
else(WIN32)
    add_executable(${ExeName} ${SOURCE_FILES})
endif(WIN32)

target_link_libraries(${ExeName} ganeshEngineCore glfw GL X11 Xxf86vm Xrandr pthread Xi Xinerama dl rt Xcursor)