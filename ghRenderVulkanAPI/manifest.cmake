#
# Rendering
#
FILE(GLOB render_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/render/*.hpp")

FILE(GLOB render_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/render/*.cpp")

source_group("Source Files\\render" FILES ${render_source_files})
source_group("Header Files\\render" FILES ${render_header_files})


set(GH_VULKAN_API_SOURCES
        ${render_source_files}
        ${render_header_files})



