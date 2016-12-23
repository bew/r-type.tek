cmake_minimum_required(VERSION 3.0)

set(LIB_NAME StateMachine)
set(TEST_EXE ${LIB_NAME}_test)
set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(${LIB_NAME})

include_directories(${LIB_INCLUDE})

add_subdirectory(test)