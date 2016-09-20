project(ganeshEngineCore)
set(LibName "ganeshEngineCore")

include_directories("Include")

set(EngineCoreSources
        "Source/ghClock.cpp"
        "Source/ghGameObject.cpp"
        "Source/ghILogger.cpp"
        "Source/ghSystem.cpp")

include_directories(
        Include/
        ../ganeshEngineUtility/Include
        ../libs/rapidjson/include
)

SET_SOURCE_FILES_PROPERTIES( ${EngineCoreSources} PROPERTIES LANGUAGE CXX )

add_library(${LibName} ${EngineCoreSources})
target_link_libraries(${LibName} ganeshEngineUtility)