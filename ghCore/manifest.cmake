#
# Util
#
FILE(GLOB util_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/util/*.hpp")

FILE(GLOB util_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/util/*.cpp")

source_group("Source Files\\util" FILES ${util_source_files})
source_group("Header Files\\util" FILES ${util_header_files})


#
# ECS
#
FILE(GLOB ecs_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/ecs/*.hpp")

FILE(GLOB ecs_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/ecs/*.cpp")

source_group("Source Files\\ecs" FILES ${ecs_source_files})
source_group("Header Files\\ecs" FILES ${ecs_header_files})


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

#
# other
#
FILE(GLOB other_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp")

FILE(GLOB other_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

source_group("Source Files" FILES ${other_source_files})
source_group("Header Files" FILES ${other_header_files})



set(CORE_SOURCES
        ${render_source_files}
        ${render_header_files}
        ${util_source_files}
        ${util_header_files}
        ${ecs_source_files}
        ${ecs_header_files}
        ${window_source_files}
        ${window_header_files}
        ${other_source_files}
        ${other_header_files})



