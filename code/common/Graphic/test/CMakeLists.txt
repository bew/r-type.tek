cmake_minimum_required(VERSION 3.0)

set(SOURCES main.cpp)
set(DEPENDENCIES)

add_executable(${TEST_EXE} ${SOURCES})
target_link_libraries(${TEST_EXE} ${DEPENDENCIES} ${LIB_NAME} gtest)
install(TARGETS ${TEST_EXE} DESTINATION bin/test)

add_custom_command(TARGET ${TEST_EXE}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/asset ${CMAKE_INSTALL_PREFIX}/bin/test/asset
  )