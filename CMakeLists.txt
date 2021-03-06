cmake_minimum_required(VERSION 3.1)

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

#Allow to use libraries on window
use_msvc_static_runtime()

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(ASSET_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asset)

add_subdirectory(vendor)
add_subdirectory(code)
add_subdirectory(doc)

install(DIRECTORY ${ASSET_DIRECTORY}
  DESTINATION bin
  )
