cmake_minimum_required(VERSION 3.0.0)

# Google test
add_subdirectory(googletest)
#add_subdirectory(SFML)

# !! IMPORTANT !!
# Each project should have their own folder "test" which is added by the root cmake
# Inside this folder the cmake should contain at least the following rules :
#
# add_executable(PROJECT_test FILES)
# target_link_libraries(PROJECT_test gtest)
#
# Where "PROJECT" is the name of project the test are generated for and "FILES" the test files
# Please see https://github.com/google/googletest/blob/master/googletest/docs/Primer.md to know how to create test files
