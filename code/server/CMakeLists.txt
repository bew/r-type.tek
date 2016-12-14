cmake_minimum_required(VERSION 3.0)

project(Server)
set(EXEC_NAME server)

set(SRV_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SRV_INCLUDE})

add_subdirectory("src")
#add_subdirectory("test")

