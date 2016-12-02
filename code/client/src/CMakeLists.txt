set(CL_SOURCE)
add(CL_SOURCE main.cpp)
set(CL_EXEC client)

add_executable(${CL_EXEC} ${CL_SOURCE})
target_link_libraries(${CL_EXEC} ${RT_COMMON_NAME})
install(TARGETS ${CL_EXEC} DESTINATION bin)
