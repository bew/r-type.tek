use_msvc_static_runtime()

add_executable(${TEST_EXE} main.cpp)
target_link_libraries(${TEST_EXE} ${LIB_TEST_NAME} gtest)

set(GENERATOR_NAME empty_test_generator)
set(GENERATOR_SOURCE empty.cpp)
add_library(${GENERATOR_NAME} SHARED ${GENERATOR_SOURCE})
target_link_libraries(${GENERATOR_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${TEST_EXE} DESTINATION bin/test)
install(TARGETS ${GENERATOR_NAME} DESTINATION bin/test/generators)
