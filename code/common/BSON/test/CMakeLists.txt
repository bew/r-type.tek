cmake_minimum_required(VERSION 3.0)

use_msvc_static_runtime()

add_executable(${TEST_EXE} main.cpp serialization.cpp miscellaneous.cpp)
target_link_libraries(${TEST_EXE} ${LIB_TEST_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)
