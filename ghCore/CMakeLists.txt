set(target_name ghCore)

include(manifest.cmake)
include_directories(Include/)

add_library(${target_name} ${CORE_SOURCES})
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${target_name} PROPERTY FOLDER "GaneshEngine")

install(TARGETS ${target_name}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)