cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES)
set(LIB_DEPEDENCIES)

if(UNIX)
  set(LIB_SOURCES ${LIB_SOURCES} linuxLibraryLoader.cpp)
  set(LIB_DEPENDENCIES ${LIB_DEPENDENCIES} dl)
elseif(WIN32)
  set(LIB_SOURCES ${LIB_SOURCES} windowsLibraryLoader.cpp)
else()
  message(ERROR "Unsupported plateform")
endif()

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )