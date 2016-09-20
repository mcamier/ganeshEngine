set(target_name ghEngine)

include(manifest.cmake)
include_directories(
		Include
		../ghCore/Include
		../libs/glm
		../libs/rapidjson/include)

add_library(${target_name} ${GH_ENGINE_SOURCES})
target_link_libraries(${target_name} ghCore)
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${target_name} PROPERTY FOLDER "GaneshEngine")



install(TARGETS ${target_name}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)