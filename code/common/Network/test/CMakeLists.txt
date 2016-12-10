set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

use_msvc_static_runtime()

add_executable(${TEST_EXE} main.cpp)

find_package (Threads)
if (Threads_FOUND)
    target_link_libraries(${TEST_EXE} Threads::Threads)
ENDIF()

target_link_libraries(${TEST_EXE} ${LIB_TEST_NAME} gtest)
 
install(TARGETS ${TEST_EXE} DESTINATION bin/test)