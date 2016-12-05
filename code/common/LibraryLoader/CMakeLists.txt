cmake_minimum_required(VERSION 3.0)

project(LibraryLoader)

set(LIBRARYLOADER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIBRARYLOADER_INCLUDE})

add_subdirectory(src)
