find_package(Git REQUIRED)

function(get_lib_from_github _folder _url _tag)
    if(NOT EXISTS "${_folder}")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} clone --branch ${_tag} ${_url} ${_folder}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_RES
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    endif()
endfunction()

set(LIB_DIR "${PROJECT_SOURCE_DIR}/libs")

if(NOT EXISTS "${LIB_DIR}")
    file(MAKE_DIRECTORY "${LIB_DIR}")
endif()

set(RAPIDJSON_URL "https://github.com/miloyip/rapidjson.git")
set(RAPIDJSON_TAG "v1.0.2")
set(RAPIDJSON_DIR "${LIB_DIR}/rapidjson")
get_lib_from_github(${RAPIDJSON_DIR} ${RAPIDJSON_URL} ${RAPIDJSON_TAG})


#set(GLM_URL "https://github.com/g-truc/glm.git")
#set(GLM_TAG "0.9.7")
#set(GLM_DIR "${LIB_DIR}/glm")
#get_lib_from_github(${GLM_DIR} ${GLM_URL} ${GLM_TAG})
#
#
#set(GTEST_URL "https://github.com/google/googletest.git")
#set(GTEST_TAG "release-1.8.0")
#set(GTEST_DIR "${LIB_DIR}/gtest")
#get_lib_from_github(${GTEST_DIR} ${GTEST_URL} ${GTEST_TAG})
#
#if(NOT EXISTS "${GLEW_DIR}/src/glew.c")
#    set(GEN_CMD "C:/MinGW/msys/1.0/bin/bash.exe")
#    message(WARNING "generate glew.c")
#    message(WARNING "${GEN_CMD} -l -c 'cd ${GLEW_DIR}/auto && make'")
#
#    execute_process(
#            COMMAND ${GEN_CMD} -l -c "cd ${GLEW_DIR}/auto && make"
#            WORKING_DIRECTORY ${GLEW_DIR}
#            OUTPUT_FILE ${LIB_DIR}/log.txt
#            RESULT_VARIABLE MAKE_GLEW_RES
#            OUTPUT_VARIABLE MAKE_GLEW_OUTPUT
#    )
#
#    # Cause compile failure on my platform if not removed before src generation
#    file(REMOVE ${GLEW_DIR}/auto/extensions/gl/GL_NV_draw_vulkan_image)
#
#    execute_process(
#            COMMAND ${GEN_CMD} -l -c "cd ${GLEW_DIR} && make install"
#            WORKING_DIRECTORY ${GLEW_DIR}
#            OUTPUT_FILE ${LIB_DIR}/log.txt
#            RESULT_VARIABLE MAKE_GLEW_RES
#            OUTPUT_VARIABLE MAKE_GLEW_OUTPUT
#    )
#
#    message(WARNING "MAKE_GLEW_RES : ${MAKE_GLEW_RES}")
#    message(WARNING "MAKE_GLEW_OUTPUT : ${MAKE_GLEW_OUTPUT}")
#endif(NOT EXISTS "${GLEW_DIR}/src/glew.c")

add_subdirectory(libs)