use_msvc_static_runtime()

add_executable(${TEST_EXE} main.cpp)
target_link_libraries(${TEST_EXE} ${LIB_TEST_NAME} BSON FSWatcher gtest)

install(TARGETS ${TEST_EXE} DESTINATION bin/test)

add_custom_command(TARGET ${TEST_EXE}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/asset ${CMAKE_INSTALL_PREFIX}/bin/test/asset
  )
