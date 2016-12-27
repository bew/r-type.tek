cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES AComponent.cpp Entity.cpp World.cpp CompEvent.cpp SysEvent.cpp CompHitbox.cpp CompMovement.cpp SysMovement.cpp CompCollision.cpp SysCollision.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompEvent.cpp SysEvent.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompHitbox.cpp CompMovement.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompLife.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompTick.cpp SysTick.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompNetworkClient.cpp CompNetworkServer.cpp)
set(LIB_SOURCES ${LIB_SOURCES} ECSLogLevel.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompStateMachine.cpp)
#graphique
set(LIB_SOURCES ${LIB_SOURCES} CompWindow.cpp SysWindow.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompAsset.cpp CompOptions.cpp CompMusic.cpp SysAsset.cpp SysMusic.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompSprite.cpp SysSprite.cpp SysController.cpp SysOptions.cpp)
set(LIB_SOURCES ${LIB_SOURCES} AssetLogLevel.cpp)
set(LIB_DEPENDENCIES Network BSON Logs Graphic)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

copy(${LIB_NAME} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})