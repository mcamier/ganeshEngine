set(target_name ghRenderOpenglAPI)

include(manifest.cmake)
include_directories(
        Include
        ../ghCore/Include)

#only this project link Gls libraries
set(GL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130)


add_library(${target_name} ${GH_GL_API_SOURCES})
target_link_libraries(${target_name} ${GL_LIBS} ghCore)
set_property(TARGET ${target_name} PROPERTY FOLDER "Plugins")

install(TARGETS ${target_name}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)