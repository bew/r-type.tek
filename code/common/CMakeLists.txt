# Set global vars

project("common")

set(RT_COMMON_NAMES)
set(RT_COMMON_TESTS_NAMES)
set(RT_COMMON_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/include)

# Add librariries
add_subdirectory(BSON)          #No dependencies
add_subdirectory(LibraryLoader) #No dependencies
add_subdirectory(Network)       #No dependencies
add_subdirectory(FSWatcher)     #No dependencies
add_subdirectory(Graphic)       #Depend On BSON, FSWatcher
#add_subdirectory(Protocol)      #Depend On Network
#ECS: depend on  a lot of things

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_TESTS_NAMES} PARENT_SCOPE)
