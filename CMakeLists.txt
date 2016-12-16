cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(vendor)

##
#  This  force MSVC to use static runtime lib.
#  This is required by googletest framework.
#  This should be used before add_executable(..) when building test.
#  And nowhere else.
##
macro(use_msvc_static_runtime)
  if(WIN32)
    foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
	    )
      if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)
  endif()
endmacro(use_msvc_static_runtime)

add_subdirectory(code)

add_subdirectory(doc)