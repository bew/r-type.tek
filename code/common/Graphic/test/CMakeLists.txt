cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp)
set(DEPENDENCIES)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} ${LIB_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)

copy(${TEST_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/asset ${CMAKE_INSTALL_PREFIX}/bin/test/asset)