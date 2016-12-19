cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCE Protocol.cpp Answers.cpp Server.cpp Client.cpp)
set(LIB_DEPENDENCIES BSON)

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
add_library(${LIB_TEST_NAME} SHARED ${LIB_SOURCE})

target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_link_libraries(${LIB_TEST_NAME} BSON_test)
install(TARGETS ${LIB_TEST_NAME} DESTINATION bin/test/lib)

target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
target_include_directories(${LIB_TEST_NAME} PUBLIC ${LIB_INCLUDE})

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_TESTS_NAMES} ${LIB_TEST_NAME} PARENT_SCOPE)

add_custom_command(TARGET ${LIB_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
  )
