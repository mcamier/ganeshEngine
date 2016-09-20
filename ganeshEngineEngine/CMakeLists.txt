project(ganeshEngineEngine)
set(LibName "ganeshEngineEngine")

find_package(OpenGL REQUIRED)

include_directories("Include")

set(EngineSources
		"Source/ghActor.cpp"
		"Source/ghApplication.cpp"
		"Source/ghClock.cpp"
		"Source/ghComponent.cpp"
		"Source/ghConsoleLogger.cpp"
		"Source/ghCore.cpp"
		"Source/ghEvent.cpp"
		"Source/ghFileLogger.cpp"
		"Source/ghFrustum.cpp"
		"Source/ghGLRendererManager.cpp"
		"Source/ghInputConfiguration.cpp"
		"Source/ghInputContext.cpp"
		"Source/ghInputManager.cpp"
		"Source/ghInputUtils.cpp"
		"Source/ghLoggerManager.cpp"
		"Source/ghMesh.cpp"
		"Source/ghModel.cpp"
		"Source/ghPlane.cpp"
		"Source/ghPlatform.cpp"
		"Source/ghProfiler.cpp"
		"Source/ghProfilerManager.cpp"
		"Source/ghResourceManager.cpp"
		"Source/ghResourceWrapper.cpp"
		"Source/ghRTTIs.cpp"
		"Source/ghScene.cpp"
		"Source/ghSceneComponent.cpp"
		"Source/ghShader.cpp"
		"Source/ghShaderProgram.cpp"
		"Source/ghTexture.cpp")

include_directories(
		Include/
		../ganeshEngineCore/Include
		../ganeshEngineUtility/Include
		../libs/glm
		../libs/glew/include
		../libs/glfw/include
		../libs/rapidjson/include)

set(GL_LIBS
		${OPENGL_LIBRARY}
		glfw
		GLEW_1130)


SET_SOURCE_FILES_PROPERTIES( ${EngineSources} PROPERTIES LANGUAGE CXX )

add_library(${LibName} ${EngineSources})
target_link_libraries(${LibName} ${GL_LIBS} ganeshEngineUtility ganeshEngineCore)


