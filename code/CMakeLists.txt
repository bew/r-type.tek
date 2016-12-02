cmake_minimum_required(VERSION 3.0)

project("r-type")

# utility function
# it allows to set a variable, then add some fields easily
#
# ex:
#
#   set(MY_VAR)
#   add(MY_VAR some)
#   add(MY_VAR fields)
#   add(MY_VAR added)
#
#   message("${MYVAR}")  => "some;fields;added"
#
function(add var_name)
	set(${var_name} ${${var_name}} ${ARGN} PARENT_SCOPE)
endfunction(add)

# MAIN COMMON LIB
#------------------------------------

set(RT_COMMON_NAME rt_common)
set(RT_COMMON_INCLUDE)
add_subdirectory("common")


message(WARNING ${RT_COMMON_INCLUDE})

# CLIENT/SERVER PROJECTS
#------------------------------------

add_subdirectory("client")
add_subdirectory("server")

# LEVEL/ENTITY/ETC GENERATORS
#------------------------------------

add_subdirectory("generators")

#add_subdirectory("doc")
