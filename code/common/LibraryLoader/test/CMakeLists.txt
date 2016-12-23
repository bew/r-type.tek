cmake_minimum_required(VERSION 3.0)

set(SOURCES main.cpp)
set(DEPENDENCIES)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} ${LIB_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)

set(GENERATOR_NAME empty_test_generator)
set(GENERATOR_SOURCE empty.cpp)
add_library(${GENERATOR_NAME} SHARED ${GENERATOR_SOURCE})
target_link_libraries(${GENERATOR_NAME} ${RT_COMMON_NAMES})
install(TARGETS ${GENERATOR_NAME} DESTINATION bin/test/generators)