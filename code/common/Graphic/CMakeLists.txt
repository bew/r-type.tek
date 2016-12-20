cmake_minimum_required(VERSION 3.0)

project(Graphic)
set(LIB_NAME Graphic)
set(LIB_TEST_NAME ${LIB_NAME}_test)
set(TEST_EXE ${LIB_TEST_NAME}_exe)

set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE} ${RT_COMMON_INCLUDES})

add_subdirectory(src)

#definitely unable to link under msvc, it just don't work at all
if(UNIX)
add_subdirectory(test)
endif()

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_TESTS_NAMES} PARENT_SCOPE)

