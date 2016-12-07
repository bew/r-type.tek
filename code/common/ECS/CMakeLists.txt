cmake_minimum_required(VERSION 3.0)

project(ECS)
set(LIB_NAME libECS)
set(LIB_TEST_NAME ${LIB_NAME}_test)

set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE})

add_subdirectory(src)
# add_subdirectory(test)

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)
