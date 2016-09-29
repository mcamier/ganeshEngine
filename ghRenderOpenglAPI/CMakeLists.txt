set(target_name ghRenderOpenglAPI)

include(manifest.cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        Include
        ../ghCore/Include
        ${GLEW_INCLUDE_DIR})


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${OPENGL_glu_LIBRARY}
            ${GLEW_LIBRARY})

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${OPENGL_glu_LIBRARY}
            ${GLEW_LIBRARY})

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${OPENGL_glu_LIBRARY}
            ${GLEW_LIBRARY})

else()
    message(FATAL_ERROR "cannot set [OPENGL_LIBRARY] on this system [${CMAKE_SYSTEM_NAME}]")
endif()

set(GL_LIBS ${OPENGL_LIBRARY})

add_library(${target_name} ${GH_GL_API_SOURCES})
target_link_libraries(${target_name} ${GL_LIBS} ghCore)
set_property(TARGET ${target_name} PROPERTY FOLDER "Plugins")

install(TARGETS ${target_name}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)