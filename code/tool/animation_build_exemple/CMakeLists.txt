cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES main.cpp)
set(LIB_DEPENDENCIES BSON)

include_directories(${RT_COMMON_INCLUDES})
add_executable(craft_anim ${LIB_SOURCES})
target_link_libraries(craft_anim ${LIB_DEPENDENCIES})
install(TARGETS craft_anim DESTINATION bin/tool)
