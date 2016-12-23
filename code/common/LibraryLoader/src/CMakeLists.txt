set(LIB_SOURCE)
set(LIB_DEPEDENCIES)

if(UNIX)
  set(LIB_SOURCE ${LIB_SOURCE} linuxLibraryLoader.cpp)
  set(LIB_DEPENDENCIES ${LIB_DEPENDENCIES} dl)
elseif(WIN32)
  set(LIB_SOURCE ${LIB_SOURCE} windowsLibraryLoader.cpp)
else()
  message(ERROR "Unsupported plateform")
endif()

cmake_minimum_required(VERSION 3.0)

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )