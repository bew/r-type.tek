cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp SysWindow.cpp CompWindow.cpp SysMusic.cpp SysKeyboard.cpp SysSprite.cpp CompOptions.cpp SysOptions.cpp SysAsset.cpp CompAsset.cpp SysMenu.cpp)
set(DEPENDENCIES ${RT_COMMON_NAMES})

add_executable(${CL_NAME} ${SOURCES})
target_link_libraries(${CL_NAME} ${DEPENDENCIES})
install(TARGETS ${CL_NAME} DESTINATION bin)
