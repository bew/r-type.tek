cmake_minimum_required(VERSION 3.0)

set(SOURCES main.cpp)
set(DEPENDENCIES ${RT_COMMON_NAMES})

add_executable(${CL_NAME} ${SOURCES})
target_link_libraries(${CL_NAME} ${DEPENDENCIES})
install(TARGETS ${CL_NAME} DESTINATION bin)