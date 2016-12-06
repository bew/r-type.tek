cmake_minimum_required(VERSION 3.0)

project(BSON)

set(BSON_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${BSON_INCLUDE})

add_subdirectory(src)
