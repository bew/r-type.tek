cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp flags.cpp)
set(DEPENDENCIES Network BSON Logs Graphic)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} ${LIB_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)