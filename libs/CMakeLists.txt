# GLM
add_subdirectory (glm)
include_directories(glm)

# RAPIDJSON
add_subdirectory (rapidjson)
include_directories(rapidjson/include)

set(RAPIDJSON_BUILD_DOC OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_TESTS OFF)

#if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
#    add_definitions( "/MP" )
#endif()
#
#add_definitions(
#        -DTW_STATIC
#        -DTW_NO_LIB_PRAGMA
#        -DTW_NO_DIRECT3D
#        -DGLEW_STATIC
#        -D_CRT_SECURE_NO_WARNINGS
#)
#
#### GTEST ###$
##add_subdirectory (gtest/googletest)
##include_directories(gtest/googletest)
#
#
#### GLFW ###
#add_subdirectory (glew)
#include_directories(glew/include/)
#
#add_subdirectory (glfw)
#include_directories(glfw/include/GLFW/)
#
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#
#if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    set(OPENGL_LIBRARY
#            ${OPENGL_LIBRARY}
#            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
#            ${CMAKE_DL_LIBS}
#            ${GLFW_LIBRARIES}
#            ${OPENGL_glu_LIBRARY}
#            )
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    set(OPENGL_LIBRARY
#            ${OPENGL_LIBRARY}
#            ${CMAKE_DL_LIBS}
#            ${GLFW_LIBRARIES}
#            ${OPENGL_glu_LIBRARY}
#            )
#else(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    set(OPENGL_LIBRARY
#            ${OPENGL_LIBRARY}
#            ${CMAKE_DL_LIBS}
#            ${GLFW_LIBRARIES}
#            ${OPENGL_glu_LIBRARY}
#            )
#endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#
#### GLEW ###
#set(GLEW_SOURCE glew/src/glew.c)
#
#set(GLEW_HEADERS )
#
#add_library( GLEW_1130 STATIC
#    ${GLEW_SOURCE}
#    ${GLEW_INCLUDE}
#)
#target_link_libraries(GLEW_1130
#    ${OPENGL_LIBRARY}
#    ${EXTRA_LIBS}
#)
#
#set_target_properties(GLEW_1130 PROPERTIES LINKER_LANGUAGE CXX)