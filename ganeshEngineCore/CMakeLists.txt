project(ganeshEngineCore)
set(LibName "ganeshEngineCore")
set(EngineInclude
    "Include")
include_directories(${EngineInclude})

set(EngineSources
        "Source/ghApplication.cpp"
        "Source/ghPlatform.cpp"
        "Source/ghClock.cpp"
        "Source/ghCore.cpp"
        "Source/ghProfilerManager.cpp"
        "Source/ghGLRendererManager.cpp"
        "Source/ghProfiler.cpp"
        "Source/ghPlane.cpp"
        "Source/ghSimulation.cpp"
        "Source/graphics/ghGLShader.cpp"
        "Source/graphics/ghGLProgram.cpp"
        "Source/graphics/ghFrustum.cpp")


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