project(ganeshEngineDemo)
set(ExeName Demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(DemoInclude
    "Include"
    "../ganeshEngineCore/Include")

include_directories (
    ${DemoInclude}
    ../libs/glm/
    ../libs/glew/include
    ../libs/glfw/include
    ../libs/rapidjson/include
)

find_package(OpenGL REQUIRED)

set(GL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130)

set(SOURCE_FILES
   "Source/main.cpp"
   "Source/kzGameplay.cpp")

SET_SOURCE_FILES_PROPERTIES( ${SOURCE_FILES} PROPERTIES LANGUAGE CXX )
add_executable(${ExeName} ${SOURCE_FILES})

target_link_libraries(${ExeName} ${GL_LIBS} ganeshEngineCore)