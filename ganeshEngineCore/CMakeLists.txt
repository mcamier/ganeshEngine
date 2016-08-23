project(ganeshEngineCore)
set(LibName "ganeshEngineCore")
set(EngineInclude
    "Include")
include_directories(${EngineInclude})

find_package(OpenGL REQUIRED)

set(EngineIncludes
        "Include/ghActor.h"
        "Include/ghApplication.h"
        "Include/ghCamera.h"
        "Include/ghClock.h"
        "Include/ghConsoleLogger.h"
        "Include/ghCore.h"
        "Include/ghDoubleBufferedStackAllocator.h"
        "Include/ghFileLogger.h"
        "Include/ghGLRendererManager.h"
        "Include/ghHeaders.h"
        "Include/ghICollider.h"
        "Include/ghILogger.h"
        "Include/ghInputManager.h"
        "Include/ghInputContext.h"
        "Include/ghInputUtils.h"
        "Include/ghLoggerManager.h"
        "Include/ghPlane.h"
        "Include/ghEvent.h"
        "Include/ghPlatform.h"
        "Include/ghPoolAllocator.h"
        "Include/ghProfiler.h"
        "Include/ghProfilerManager.h"
        "Include/ghScene.h"
        "Include/ghMath.h"
        "Include/ghResource.h"
        "Include/ghResourceWrapper.h"
        "Include/ghResourceHandler.h"
        "Include/ghResourceManager.h"
        "Include/ghResourceLoader.h"
        "Include/ghSceneObject.h"
        "Include/ghSkybox.h"
        "Include/ghStackAllocator.h"
        "Include/graphics/ghFrustum.h"
        "Include/graphics/ghGLProgram.h"
        "Include/graphics/ghGLModel.h"
        "Include/graphics/ghGLShader.h")

set(EngineSources
        "Source/ghActor.cpp"
        "Source/ghApplication.cpp"
        "Source/ghCamera.cpp"
        "Source/ghClock.cpp"
        "Source/ghConsoleLogger.cpp"
        "Source/ghCore.cpp"
        "Source/ghDoubleBufferedStackAllocator.cpp"
        "Source/ghFileLogger.cpp"
        "Source/ghInputManager.cpp"
        "Source/ghInputContext.cpp"
        "Source/ghInputUtils.cpp"
        "Source/ghGLRendererManager.cpp"
        "Source/ghLoggerManager.cpp"
        "Source/ghPlane.cpp"
	    "Source/ghMath.cpp"
        "Source/ghPlatform.cpp"
        "Source/ghPoolAllocator.cpp"
        "Source/ghProfiler.cpp"
        "Source/ghProfilerManager.cpp"
        "Source/ghScene.cpp"
        "Source/ghEvent.cpp"
        "Source/ghResourceManager.cpp"
        "Source/ghResourceWrapper.cpp"
        "Source/ghSceneObject.cpp"
        "Source/ghSkybox.cpp"
        "Source/ghStackAllocator.cpp"
        "Source/graphics/ghFrustum.cpp"
        "Source/graphics/ghGLMesh.cpp"
        "Source/graphics/ghGLModel.cpp"
        "Source/graphics/ghGLTexture.cpp"
        "Source/graphics/ghGLProgram.cpp"
        "Source/graphics/ghGLShader.cpp")

SET_SOURCE_FILES_PROPERTIES( ${EngineSources} PROPERTIES LANGUAGE CXX )

include_directories(
        ../ganeshEngineCore/Include
        ../libs/glm
        ../libs/glew/include
        ../libs/glfw/include
        ../libs/rapidjson/include
        )

set(GL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        GLEW_1130)

add_library(${LibName} ${EngineSources})
target_link_libraries(${LibName} ${GL_LIBS})

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT doxygen.cfg)
    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doc)

    add_custom_command(
            OUTPUT ${DOXYGEN_OUTPUT}
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${DOXYGEN_INPUT}
    )

    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

    add_custom_target(apidoc_forced
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
endif(DOXYGEN_FOUND)
