set(CL_SOURCE)
add(CL_SOURCE WindowComponent.cpp WindowSystem.cpp main.cpp)
set(CL_EXEC client)

add_executable(${CL_EXEC} ${CL_SOURCE})
target_link_libraries(${CL_EXEC} sfml-graphics sfml-window sfml-audio sfml-system ${RT_COMMON_NAMES})
install(TARGETS ${CL_EXEC} DESTINATION bin)
