cmake_minimum_required(VERSION 3.0)

project(Graphic)
set(LIB_NAME Graphic)
set(LIB_TEST_NAME ${LIB_NAME}_test)
set(TEST_EXE ${LIB_TEST_NAME}_exe)

set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include ${RT_COMMON_INCLUDES})
include_directories(${LIB_INCLUDE})

add_subdirectory(src)
add_subdirectory(test)

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)
