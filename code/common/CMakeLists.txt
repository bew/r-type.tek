# Set global vars

project("common")

set(RT_COMMON_NAMES)
set(RT_COMMON_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/include)

# Add librariries
add_subdirectory(BSON)
add_subdirectory(LibraryLoader)
add_subdirectory(Network)
add_subdirectory(SFML)

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)

message(STATUS "The common libraries names are : \n ${RT_COMMON_NAMES}\nIf something is missing, please check RT_COMMON_NAMES scope")
