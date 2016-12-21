set(CL_SOURCE)
add(CL_SOURCE CompWindow.cpp SysWindow.cpp main.cpp)
add(CL_SOURCE CompAsset.cpp CompOptions.cpp CompMusic.cpp SysAsset.cpp SysMusic.cpp ${CL_SOURCE})
add(CL_SOURCE CompSprite.cpp SysSprite.cpp SysController.cpp SysOptions.cpp ${CL_SOURCE})
set(CL_EXEC client)

add_executable(${CL_EXEC} ${CL_SOURCE})
target_link_libraries(${CL_EXEC} sfml-graphics sfml-window sfml-audio sfml-system ${RT_COMMON_NAMES})
install(TARGETS ${CL_EXEC} DESTINATION bin)
