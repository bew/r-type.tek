cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCES AFileSystemWatcher.cpp)
set(LIB_DEPEDENCIES)

if(UNIX)
  set(LIB_SOURCES ${LIB_SOURCES} linuxFileSystemWatcher.cpp)
elseif(WIN32)
  set(LIB_SOURCES ${LIB_SOURCES} windowsFileSystemWatcher.cpp)
else()
  message(ERROR "Unsupported plateform")
endif()

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})

add_custom_command(TARGET ${LIB_NAME}
                   POST_BUILD
                   COMMAND  ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
                   )