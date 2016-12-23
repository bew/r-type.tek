set(CL_EXEC client)
set(CL_SOURCE main.cpp)

add_definitions(-DSFML_STATIC)

add_executable(${CL_EXEC} ${CL_SOURCE})
target_link_libraries(${CL_EXEC} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${RT_COMMON_NAMES})
install(TARGETS ${CL_EXEC} DESTINATION bin)