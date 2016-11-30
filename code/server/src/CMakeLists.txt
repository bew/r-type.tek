set(SV_SOURCE)

# SERVER sources
#------------------------------------

add(SV_SOURCE some.cpp)
#add(SV_SOURCE file.cpp)

set(SV_EXEC server)
add_executable(${SV_EXEC} ${SV_SOURCE})
target_link_libraries(${SV_EXEC} ${RT_COMMON_NAME})

install(TARGETS ${SV_EXEC} DESTINATION bin)
