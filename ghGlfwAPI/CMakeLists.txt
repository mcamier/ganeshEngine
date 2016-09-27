set(target_name ghGlfwAPI)

find_package(GLFW REQUIRED)

include_directories(
        Include
        ../ghCore/Include
        ${GLFW_INCLUDE_DIR})

include(manifest.cmake)


add_library(${target_name} ${GH_GLFW_API_SOURCES})
#only this project link GLFW librarie
target_link_libraries(${target_name} ${GLFW_glfw_LIBRARY} ghCore)
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${target_name} PROPERTY FOLDER "Plugins")

install(TARGETS ${target_name}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)