cmake_minimum_required(VERSION 3.1)

set(LIB_NAME Graphic)
set(TEST_EXE ${LIB_NAME}_test)
set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)

project(${LIB_NAME})

include_directories(${LIB_INCLUDE})

add_subdirectory(src)
add_subdirectory(test)