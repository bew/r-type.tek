cmake_minimum_required(VERSION 3.1)

set(SRV_SOURCE)

add(SRV_SOURCE ServerLogLevel.cpp)
add(SRV_SOURCE Router.cpp)
add(SRV_SOURCE Server.cpp)
add(SRV_SOURCE main.cpp)
add(SRV_SOURCE ClientCommandsState.cpp)
add(SRV_SOURCE ServerRouter.cpp)
add(SRV_SOURCE CompSound.cpp)
add(SRV_SOURCE CompNetworkServer.cpp)


set(DEPENDENCIES ${RT_COMMON_NAMES})

add_executable(${EXEC_NAME} ${SRV_SOURCE})
target_link_libraries(${EXEC_NAME} ${RT_COMMON_NAMES})

install(TARGETS ${EXEC_NAME} DESTINATION bin)

