#
# Rendering
#
FILE(GLOB render_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/render/*.hpp")

FILE(GLOB render_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/render/*.cpp")

source_group("Source Files\\render" FILES ${render_source_files})
source_group("Header Files\\render" FILES ${render_header_files})

#
# Window
#
FILE(GLOB window_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/window/*.hpp")

FILE(GLOB window_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/window/*.cpp")

source_group("Source Files\\window" FILES ${window_source_files})
source_group("Header Files\\window" FILES ${window_header_files})


set(CORE_SOURCES
        ${render_source_files}
        ${render_header_files}
        ${window_source_files}
        ${window_header_files})



