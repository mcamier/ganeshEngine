# RAPIDJSON
add_subdirectory (rapidjson)
include_directories(rapidjson/include)

set(RAPIDJSON_BUILD_DOC OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_TESTS OFF)
if(IS_BIG_ENDIAN)
	set(RAPIDJSON_ENDIAN RAPIDJSON_BIGENDIAN)
else()
	set(RAPIDJSON_ENDIAN RAPIDJSON_LITTLEENDIAN)
endif()

#if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
#    add_definitions( "/MP" )
#endif()
#
#### GTEST ###$
##add_subdirectory (gtest/googletest)
##include_directories(gtest/googletest)