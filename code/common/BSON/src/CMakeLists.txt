cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES Document.cpp)
set(LIB_DEPENDENCIES)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

copy(${LIB_NAME} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})