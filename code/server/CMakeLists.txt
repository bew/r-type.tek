cmake_minimum_required(VERSION 3.0)

set(SRV_NAME server)
set(SRV_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(${SRV_NAME})

include_directories(${SRV_INCLUDE} ${RT_COMMON_INCLUDES})

add_subdirectory(src)