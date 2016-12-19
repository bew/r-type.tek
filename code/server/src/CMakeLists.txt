set(SRV_SOURCE)

add(SRV_SOURCE Account.cpp)
add(SRV_SOURCE Player.cpp)
add(SRV_SOURCE Room.cpp)
add(SRV_SOURCE Router.cpp)
add(SRV_SOURCE Server.cpp)

add_executable(${EXEC_NAME} ${SRV_SOURCE})
target_link_libraries(${EXEC_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${EXEC_NAME} DESTINATION bin)
