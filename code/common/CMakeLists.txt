cmake_minimum_required(VERSION 3.0)

project("common")

set(RT_COMMON_NAMES)
set(RT_COMMON_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${RT_COMMON_INCLUDES})

# Libraries
add_subdirectory(Logs)          #No dependencies
add_subdirectory(Concurrency)   #No dependencies
add_subdirectory(BSON)          #No dependencies
add_subdirectory(LibraryLoader) #No dependencies
add_subdirectory(Network)       #No dependencies
add_subdirectory(FSWatcher)     #No dependencies
add_subdirectory(StateMachine)  #No dependencies
add_subdirectory(Protocol)      #Depend On BSON
add_subdirectory(Graphic)       #Depend On BSON, FSWatcher
add_subdirectory(ECS)		    #Depend on a lot of things

set(RT_COMMON_INCLUDES ${RT_COMMON_INCLUDES} PARENT_SCOPE)
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)