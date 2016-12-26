set(LIB_SOURCE main.cpp)
set(LIB_DEPENDENCIES BSON)

find_program (NPM npm)
if(NPM_FOUND)
  install(TARGETS json_to_bson DESTINATION bin/tool)
else()
  message(WARNING "Cannot find npm, skipping json_to_bson")
endif()

include_directories(${RT_COMMON_INCLUDES})
add_executable(craft_anim ${LIB_SOURCE})
target_link_libraries(craft_anim ${LIB_DEPENDENCIES})
install(TARGETS json_to_bson DESTINATION bin/tool)
