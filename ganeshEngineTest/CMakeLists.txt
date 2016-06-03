project(ganeshEngineTest)
set(LibName "ganeshEngineTest")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_OS_CYGWIN=1")

set(EngineTestSources
        "Tests/ghPlaneTest.cpp"
        "Tests/ghFrustumTest.cpp"
        "Tests/main.cpp")

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
endif()

include_directories(../ganeshEngineCore/Include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
enable_testing()

add_executable(${LibName} ${EngineTestSources})
target_link_libraries(${LibName} ${GTEST_LIBRARIES} pthread ganeshEngineCore)
add_test(${LibName} ${LibName})
