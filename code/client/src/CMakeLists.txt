cmake_minimum_required(VERSION 3.1)

set(SOURCES main.cpp SysWindow.cpp CompWindow.cpp SysMusic.cpp SysKeyboard.cpp SysSprite.cpp CompOptions.cpp SysOptions.cpp SysAsset.cpp CompAsset.cpp SysSound.cpp CompSound.cpp SysGui.cpp)
set(DEPENDENCIES ${RT_COMMON_NAMES})

if(WIN32)
    set(DEPENDENCIES ${DEPENDENCIES} ws2_32)
endif()

add_executable(${CL_NAME} ${SOURCES})
target_link_libraries(${CL_NAME} ${DEPENDENCIES})
install(TARGETS ${CL_NAME} DESTINATION bin)
