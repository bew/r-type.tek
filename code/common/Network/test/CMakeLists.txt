cmake_minimum_required(VERSION 3.0)

add_executable(${TEST_EXE} main.cpp)
target_link_libraries(${TEST_EXE} ${LIB_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)