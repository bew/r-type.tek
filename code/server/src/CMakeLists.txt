cmake_minimum_required(VERSION 3.1)

set(SOURCES some.cpp)
set(DEPENDENCIES ${RT_COMMON_NAMES})

add_executable(${SRV_NAME} ${SOURCES})
target_link_libraries(${SRV_NAME} ${DEPENDENCIES})
install(TARGETS ${SRV_NAME} DESTINATION bin)