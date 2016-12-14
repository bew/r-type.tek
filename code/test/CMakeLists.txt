set(TEST_EXE integration_test_exe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

use_msvc_static_runtime()

set(SOURCE_FILES main.cpp TestClientUDP.cpp TestServerUDP.cpp)
add_executable(${TEST_EXE} ${SOURCE_FILES})

target_link_libraries(${TEST_EXE} ${RT_COMMON_NAMES} gtest)

install(TARGETS ${TEST_EXE} DESTINATION bin/test)