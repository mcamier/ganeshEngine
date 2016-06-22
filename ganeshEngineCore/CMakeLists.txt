project(ganeshEngineCore)
set(LibName "ganeshEngineCore")
set(EngineInclude
    "Include")
include_directories(${EngineInclude})

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
        "Include/ghLoggerManager.h"
        "Include/ghPlane.h"
        "Include/ghPlatform.h"
        "Include/ghPoolAllocator.h"
        "Include/ghProfiler.h"
        "Include/ghProfilerManager.h"
        "Include/ghScene.h"
        "Include/ghSceneObject.h"
        "Include/ghSkybox.h"
        "Include/ghSimulation.h"
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
        "Source/ghGLRendererManager.cpp"
        "Source/ghLoggerManager.cpp"
        "Source/ghPlane.cpp"
        "Source/ghPlatform.cpp"
        "Source/ghPoolAllocator.cpp"
        "Source/ghProfiler.cpp"
        "Source/ghProfilerManager.cpp"
        "Source/ghScene.cpp"
        "Source/ghSceneObject.cpp"
        "Source/ghSkybox.cpp"
        "Source/ghSimulation.cpp"
        "Source/ghStackAllocator.cpp"
        "Source/graphics/ghFrustum.cpp"
        "Source/graphics/ghGLMesh.cpp"
        "Source/graphics/ghGLModel.cpp"
        "Source/graphics/ghGLTexture.cpp"
        "Source/graphics/ghGLProgram.cpp"
        "Source/graphics/ghGLShader.cpp")


find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
endif()


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()


add_library(${LibName} ${EngineSources})

if(WIN32)
    target_link_libraries(${LibName} glfw kernel32 user32 gdi32 comdlg32 advapi32 shell32 ole32 oleaut32 odbc32 winspool uuid odbccp32)
else(WIN32)
    target_link_libraries(${LibName} glfw GL X11 Xxf86vm Xrandr pthread Xi Xinerama dl rt Xcursor)
endif(WIN32)



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
