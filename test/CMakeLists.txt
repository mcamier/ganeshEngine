project(ganeshEngineTest)
set(LibName "ganeshEngineTest")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
#-DGTEST_OS_CYGWIN=1

set(EngineTestSources
        "Tests/ghPlaneTest.cpp"
        "Tests/ghMemoryTest.cpp"
        "Tests/ghFrustumTest.cpp"
        "Tests/main.cpp")

enable_testing()

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIR})
endif()

include_directories(
        ../ganeshEngineCore/Include
        ../libs/gtest/googletest/include
        ../libs/glm
        ../libs/glew/include
        ../libs/glfw/include)

add_executable(${LibName} ${EngineTestSources})
target_link_libraries(${LibName} ${GTEST_LIBRARIES} pthread ganeshEngineCore)
add_test(${LibName} ${LibName})
