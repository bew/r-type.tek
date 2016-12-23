cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCE Protocol.cpp Answers.cpp Server.cpp Client.cpp)
add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
target_link_libraries(${LIB_NAME} BSON)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )