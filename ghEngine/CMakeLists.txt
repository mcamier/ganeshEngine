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


if(WITH_GLFW)
	message("-- Use GLFW as as window and input wrapper")
	include_directories(../ghGlfwAPI/Include)
	target_link_libraries(${target_name} ghGlfwAPI)
	set_target_properties(${target_name} PROPERTIES COMPILE_FLAGS "-DUSE_GLFW_API")
else()
	message(FATAL_ERROR "No rendering API found")
endif()


install(TARGETS ${target_name}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)