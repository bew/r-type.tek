cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCE AComponent.cpp Entity.cpp World.cpp CompEvent.cpp SysEvent.cpp CompHitbox.cpp CompMovement.cpp SysMovement.cpp CompCollision.cpp SysCollision.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompEvent.cpp SysEvent.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompHitbox.cpp CompMovement.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompLife.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompTick.cpp SysTick.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompNetworkClient.cpp CompNetworkServer.cpp)
set(LIB_SOURCE ${LIB_SOURCE} ECSLogLevel.cpp)
#graphique
set(LIB_SOURCE ${LIB_SOURCE} CompWindow.cpp SysWindow.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompAsset.cpp CompOptions.cpp CompMusic.cpp SysAsset.cpp SysMusic.cpp)
set(LIB_SOURCE ${LIB_SOURCE} CompSprite.cpp SysSprite.cpp SysController.cpp SysOptions.cpp)
set(LIB_SOURCE ${LIB_SOURCE} AssetLogLevel.cpp)

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
set(LIB_DEPENDENCIES Network BSON Logs Graphic)
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)

add_custom_command(TARGET ${LIB_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
    )