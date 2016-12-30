cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp simpleClientTest.cpp ClientTest.cpp)
set(DEPENDENCIES)

if(WIN32)
    set(DEPENDENCIES ${DEPENDENCIES} ws2_32)
endif()

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} ${LIB_NAME} ECS gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)