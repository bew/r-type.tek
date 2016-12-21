set(LIB_SOURCE AComponent.cpp Entity.cpp World.cpp CompEvent.cpp SysEvent.cpp CompHitbox.cpp CompMovement.cpp SysMovement.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompEvent.cpp SysEvent.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompHitbox.cpp CompMovement.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompLife.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompTick.cpp SysTick.cpp)

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
add_library(${LIB_TEST_NAME} SHARED ${LIB_SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_link_libraries(${LIB_TEST_NAME} ${LIB_DEPENDENCIES})
target_link_libraries(${LIB_NAME} BSON)
install(TARGETS ${LIB_TEST_NAME} DESTINATION bin/test/lib)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
target_include_directories(${LIB_TEST_NAME} PUBLIC ${LIB_INCLUDE})
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_TESTS_NAMES} ${LIB_TEST_NAME} PARENT_SCOPE)
add_custom_command(TARGET ${LIB_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
  )
