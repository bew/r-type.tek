cmake_minimum_required(VERSION 3.1)

set(SRV_SOURCE)

add(SRV_SOURCE ServerLogLevel.cpp)
add(SRV_SOURCE Account.cpp)
add(SRV_SOURCE Player.cpp)
add(SRV_SOURCE Room.cpp)
add(SRV_SOURCE Router.cpp)
add(SRV_SOURCE Server.cpp)
add(SRV_SOURCE main.cpp)

set(DEPENDENCIES ${RT_COMMON_NAMES})

add_executable(${EXEC_NAME} ${SRV_SOURCE})
target_link_libraries(${EXEC_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${EXEC_NAME} DESTINATION bin)

