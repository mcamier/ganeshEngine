project(ganeshEngineUtility)
set(LibName "ganeshEngineUtility")

include_directories("Include")

set(EngineUtilitySources
		"Source/ghDoubleBufferedStackAllocator.cpp"
		"Source/ghIStream.cpp"
		"Source/ghMath.cpp"
		"Source/ghPoolAllocator.cpp"
		"Source/ghRTTI.cpp"
		"Source/ghStackAllocator.cpp"
		"Source/ghStringId.cpp"
		"Source/ghTypes.cpp")

include_directories(../libs/glm)

SET_SOURCE_FILES_PROPERTIES( ${EngineUtilitySources} PROPERTIES LANGUAGE CXX )

add_library(${LibName} ${EngineUtilitySources})