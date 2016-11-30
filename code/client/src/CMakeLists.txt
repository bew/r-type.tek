set(CL_SOURCE)

# CLIENT sources
#------------------------------------

add(CL_SOURCE some.cpp)
#add(CL_SOURCE file.cpp)

set(CL_EXEC client)
add_executable(${CL_EXEC} ${CL_SOURCE})
target_link_libraries(${CL_EXEC} ${RT_COMMON_NAME})

install(TARGETS ${CL_EXEC} DESTINATION bin)
