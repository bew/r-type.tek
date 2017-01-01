cmake_minimum_required(VERSION 3.1)

set(SRV_SOURCE)

add(SRV_SOURCE ServerLogLevel.cpp)
add(SRV_SOURCE Room.cpp)
add(SRV_SOURCE Router.cpp)
add(SRV_SOURCE Server.cpp)
add(SRV_SOURCE main.cpp)
add(SRV_SOURCE ClientCommandsState.cpp)
add(SRV_SOURCE ServerRouter.cpp)
add(SRV_SOURCE Game.cpp)
add(SRV_SOURCE CompNetworkServer.cpp)
add(SRV_SOURCE SysSerialisation.cpp)

set(DEPENDENCIES ${RT_COMMON_NAMES})

if(WIN32)
    set(DEPENDENCIES ${DEPENDENCIES} ws2_32)
endif()

add_executable(${EXEC_NAME} ${SRV_SOURCE})
target_link_libraries(${EXEC_NAME} ${DEPENDENCIES})

install(TARGETS ${EXEC_NAME} DESTINATION bin)

