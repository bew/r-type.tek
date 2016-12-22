set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

use_msvc_static_runtime()

set(SOURCE_FILES main.cpp StateTest.cpp)
add_executable(${TEST_EXE} ${SOURCE_FILES})

target_link_libraries(${TEST_EXE} gtest)

install(TARGETS ${TEST_EXE} DESTINATION bin/test)