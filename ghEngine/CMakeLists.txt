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


if(WITH_GLFW_API)
	message("-- Use GLFW as window and input wrapper")
	include_directories(../ghGlfwAPI/Include)
	target_link_libraries(${target_name} ghGlfwAPI)
	add_definitions(-DUSE_GLFW_WRAPPER_API)
else()
	message(FATAL_ERROR "No window wrapper API found")
endif()


if(WITH_RENDER_API_GL)
	message("-- Use OpenGL as rendering API")
	include_directories(../ghRenderOpenglAPI/Include)
	target_link_libraries(${target_name} ghRenderOpenglAPI)
	set_target_properties(${target_name} PROPERTIES COMPILE_FLAGS "-DUSE_RENDER_API_GL")

elseif(WITH_RENDER_API_VULKAN)
	message("-- Use Vulkan as rendering API")
	include_directories(../ghRenderVulkanAPI/Include)
	target_link_libraries(${target_name} ghRenderVulkanAPI)
	set_target_properties(${target_name} PROPERTIES COMPILE_FLAGS "-DUSE_RENDER_API_VULKAN")

else()
	message(FATAL_ERROR "No rendering API found")
endif()


install(TARGETS ${target_name}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)