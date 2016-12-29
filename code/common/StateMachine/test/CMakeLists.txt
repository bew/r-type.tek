cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp StateTest.cpp StateMachineTest.cpp)
set(DEPENDENCIES)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)

# ${LIB_NAME} is not a target, using the TEST as trigger
copy(${TEST_EXE} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})
