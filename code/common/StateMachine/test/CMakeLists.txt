cmake_minimum_required(VERSION 3.0)

set(SOURCES main.cpp StateTest.cpp StateMachineTest.cpp)
set(DEPENDENCIES)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)