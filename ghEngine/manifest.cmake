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
# Event
#
FILE(GLOB event_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/event/*.hpp")

FILE(GLOB event_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/event/*.cpp")

source_group("Source Files\\event" FILES ${event_source_files})
source_group("Header Files\\event" FILES ${event_header_files})


#
# Input
#
FILE(GLOB input_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/input/*.hpp")

FILE(GLOB input_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/input/*.cpp")

source_group("Source Files\\input" FILES ${input_source_files})
source_group("Header Files\\input" FILES ${input_header_files})


#
# Memory
#
FILE(GLOB memory_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/memory/*.hpp")

FILE(GLOB memory_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/memory/*.cpp")

source_group("Source Files\\memory" FILES ${memory_source_files})
source_group("Header Files\\memory" FILES ${memory_header_files})


#
# Render
#
FILE(GLOB render_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/render/*.hpp")

FILE(GLOB render_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/render/*.cpp")

source_group("Source Files\\render" FILES ${render_source_files})
source_group("Header Files\\render" FILES ${render_header_files})


#
# Resource
#
FILE(GLOB resource_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/resource/*.hpp")

FILE(GLOB resource_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/resource/*.cpp")

source_group("Source Files\\render" FILES ${resource_source_files})
source_group("Header Files\\render" FILES ${resource_header_files})


#
# Util
#
FILE(GLOB util_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/util/*.hpp")

FILE(GLOB util_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/util/*.cpp")

source_group("Source Files\\render" FILES ${util_source_files})
source_group("Header Files\\render" FILES ${util_header_files})


#
# others
#
FILE(GLOB other_source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp")

FILE(GLOB other_header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

source_group("Source Files" FILES ${other_source_files})
source_group("Header Files" FILES ${other_header_files})


set(GH_ENGINE_SOURCES
        ${ecs_source_files}
        ${ecs_header_files}
        ${event_source_files}
        ${event_header_files}
        ${input_source_files}
        ${input_header_files}
        ${memory_source_files}
        ${memory_header_files}
        ${render_source_files}
        ${render_header_files}
        ${resource_source_files}
        ${resource_header_files}
        ${util_source_files}
        ${util_header_files}
        ${other_source_files}
        ${other_header_files})



