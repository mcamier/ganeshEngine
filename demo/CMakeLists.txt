set(ExeName Demo)

include_directories (
    Include
    ../ghCore/Include
    ../ghEngine/Include
    ../libs/rapidjson/include)

set(demo_SRC
        "Source/main.cpp"
        "Source/TeapotActor.cpp")

set_source_files_properties( ${demo_SRC} PROPERTIES LANGUAGE CXX )

add_executable(${ExeName} ${demo_SRC})
target_link_libraries(${ExeName} ghCore ghEngine)

set_property(TARGET ${ExeName} PROPERTY FOLDER "Others")