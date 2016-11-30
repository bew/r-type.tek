set(HP_SOURCE)

add(HP_SOURCE AGenerator.cpp)
#add(HP_SOURCE some_file.cpp)

add_library(${RT_GEN_COMMON_NAME} ${HP_SOURCE})
