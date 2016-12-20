cmake_minimum_required(VERSION 3.0)

project("r-type")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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

macro(suffix_list var suffix)
	SET(listVar "")
	FOREACH(f ${ARGN})
		LIST(APPEND listVar "${f}${suffix}")
	ENDFOREACH(f)
	SET(${var} "${listVar}" PARENT_SCOPE)
endmacro(suffix_list)

# MAIN COMMON LIB
#------------------------------------
set(RT_COMMON_NAMES)
set(RT_COMMON_INCLUDE)
add_subdirectory("common")

# CLIENT/SERVER PROJECTS
#------------------------------------

add_subdirectory("client")
add_subdirectory("server")

# LEVEL/ENTITY/ETC GENERATORS
#------------------------------------

add_subdirectory("generators")

# Integration tests
#------------------------------------

add_subdirectory("test")
add_subdirectory("tool")
