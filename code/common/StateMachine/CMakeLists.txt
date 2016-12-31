cmake_minimum_required(VERSION 3.1)

set(LIB_NAME StateMachine)
set(TEST_EXE ${LIB_NAME}_test)
set(LIB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(${LIB_NAME})

include_directories(${LIB_INCLUDE})

add_subdirectory(test)

# ${LIB_NAME} is not a target, using the TEST as trigger
# see test's CMakeLists for more
