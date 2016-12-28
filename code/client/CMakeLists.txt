cmake_minimum_required(VERSION 3.1)

set(CL_NAME client)
set(TEST_EXE ${CL_NAME}_test)
set(CL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(${CL_NAME})

include_directories(${CL_INCLUDE} ${RT_COMMON_INCLUDES})

add_subdirectory(src)
add_subdirectory(test)