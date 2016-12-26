set(TEST_EXE integration_test_exe)

set(SOURCES main.cpp TestClientUDP.cpp TestServerUDP.cpp TestClientTCP.cpp TestServerTCP.cpp)
set(DEPENDENCIES ${RT_COMMON_NAMES})

include_directories(${RT_COMMON_INCLUDES})
add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)