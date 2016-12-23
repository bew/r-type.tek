cmake_minimum_required(VERSION 3.0)

set(CL_NAME client)
set(CL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(${CL_NAME})

include_directories(${LIB_INCLUDE} ${RT_COMMON_INCLUDES})

add_subdirectory(src)