set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(${LIB_TEST_NAME}_exe main.cpp)
include_directories(${LIB_TEST_NAME}_exe ${gtest_SOURCE_DIR}/include)
target_link_libraries(${LIB_TEST_NAME}_exe ${LIB_TEST_NAME} gtest)

set(GENERATOR_NAME empty_test_generator)
set(GENERATOR_SOURCE empty.cpp)
add_library(${GENERATOR_NAME} SHARED ${GENERATOR_SOURCE})
target_link_libraries(${GENERATOR_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${LIB_TEST_NAME}_exe DESTINATION bin/test)
install(TARGETS ${GENERATOR_NAME} DESTINATION bin/test/generators)
