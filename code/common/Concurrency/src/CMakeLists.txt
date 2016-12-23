cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCES ATask.cpp)
set(LIB_DEPENDENCIES)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )