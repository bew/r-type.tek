set(SV_SOURCE)

add(SV_SOURCE some.cpp ServerLogLevel.cpp)

set(SV_EXEC server)
add_executable(${SV_EXEC} ${SV_SOURCE})
target_link_libraries(${SV_EXEC} ${RT_COMMON_NAMES})
install(TARGETS ${SV_EXEC} DESTINATION bin)
