set(LEVELS_SOURCE)

# THIS IS AN EXEMPLE, THE ARCHI CAN CHANGE !
#---------------------------------------------------------
# this file will generate a dynamic lib for each level generator
# +
# 1 dyn-lib for all levels

# level 01
#------------------------------------

set(LEVEL01_LIB level01)

set(LEVEL01_SRC)
add(LEVEL01_SRC level01/generator.cpp)

add_library(${LEVEL01_LIB} SHARED ${LEVEL01_SRC} level01/entrypoint.cpp)
target_link_libraries(${LEVEL01_LIB} ${RT_GEN_COMMON_NAME})

# level 02
#------------------------------------

set(LEVEL02_LIB level02)

set(LEVEL02_SRC)
add(LEVEL02_SRC level02/generator.cpp)

add_library(${LEVEL02_LIB} SHARED ${LEVEL02_SRC} level02/entrypoint.cpp)
target_link_libraries(${LEVEL02_LIB} ${RT_GEN_COMMON_NAME})

# all levels
#------------------------------------

set(LEVELS_LIB gen_levels)

set(LEVELS_SRC)
add(LEVELS_SRC ${LEVEL01_SRC})
add(LEVELS_SRC ${LEVEL02_SRC})

add_library(${LEVELS_LIB} SHARED ${LEVELS_SRC} all_entrypoint.cpp)
target_link_libraries(${LEVELS_LIB} ${RT_GEN_COMMON_NAME})
