set(LIB_SOURCE main.cpp)
set(LIB_DEPENDENCIES BSON)

add_executable(craft_anim ${LIB_SOURCE})
target_link_libraries(craft_anim ${LIB_DEPENDENCIES})
install(TARGETS craft_anim DESTINATION bin/tool)
