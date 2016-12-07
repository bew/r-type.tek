set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

use_msvc_static_runtime()

add_executable(${LIB_TEST_NAME}_exe main.cpp serialization.cpp miscellaneous.cpp)
target_link_libraries(${LIB_TEST_NAME}_exe ${LIB_TEST_NAME} gtest)
install(TARGETS ${LIB_TEST_NAME}_exe DESTINATION bin/test)
