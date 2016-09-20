#
# Window
#
FILE(GLOB window_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/window/*.hpp")

FILE(GLOB window_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/window/*.cpp")

source_group("Source Files\\render" FILES ${window_source_files})
source_group("Header Files\\render" FILES ${window_header_files})


set(GH_GLFW_API_SOURCES
        ${window_source_files}
        ${window_header_files})



