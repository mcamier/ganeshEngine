set(LibName "ghTest")

set(EngineTestSources
        "tests/ghPlaneTest.cpp"
        "tests/ghMemoryTest.cpp"
        "tests/ghFrustumTest.cpp"
        "main.cpp")

include_directories(
        ../ghCore/Include
        ../ghEngine/Include)

add_executable(${LibName} ${EngineTestSources})
target_link_libraries(${LibName} ${GTEST_LIBRARIES} pthread ghCore ghEngine)

add_test(${LibName} ${LibName})
