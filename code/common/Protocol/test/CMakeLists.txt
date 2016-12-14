use_msvc_static_runtime()

add_executable(${TEST_EXE} main.cpp answers.cpp)
target_link_libraries(${TEST_EXE} ${LIB_TEST_NAME} BSON_test gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)
