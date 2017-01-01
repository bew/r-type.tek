cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES AComponent.cpp Entity.cpp World.cpp CompEvent.cpp SysEvent.cpp CompHitbox.cpp CompMovement.cpp SysMovement.cpp CompCollision.cpp SysCollision.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompLife.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompTick.cpp SysTick.cpp)
set(LIB_SOURCES ${LIB_SOURCES} ECSLogLevel.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompController.cpp SysController.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompProjectile.cpp CompBlueprint.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompMusic.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompSprite.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompDeath.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompSuccessor.cpp)
set(LIB_SOURCES ${LIB_SOURCES} SysDeath.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompDamage.cpp)
set(LIB_SOURCES ${LIB_SOURCES} SysDamage.cpp)
set(LIB_SOURCES ${LIB_SOURCES} SysLife.cpp)
set(LIB_SOURCES ${LIB_SOURCES} AssetLogLevel.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompType.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompIA.cpp)
set(LIB_SOURCES ${LIB_SOURCES} SysIA.cpp)
set(LIB_SOURCES ${LIB_SOURCES} CompScore.cpp)

set(LIB_DEPENDENCIES Network BSON Logs Graphic Protocol)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

copy(${LIB_NAME} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})
add_custom_command(TARGET ${LIB_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../StateMachine/include ${RT_COMMON_INCLUDES}/StateMachine
	)
