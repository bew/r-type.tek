set(SRV_SOURCE)

add(SRV_SOURCE some.cpp)

add_executable(${EXEC_NAME} ${SRV_SOURCE})
target_link_libraries(${EXEC_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${EXEC_NAME} DESTINATION bin)
