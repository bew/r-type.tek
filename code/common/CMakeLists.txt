# Set global vars

project("common")

set(RT_COMMON_NAMES)
set(RT_COMMON_TESTS_NAMES)
set(RT_COMMON_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/include)

# Add librariries
add_subdirectory(BSON)
add_subdirectory(LibraryLoader)
add_subdirectory(Network)
add_subdirectory(FSWatcher)
add_subdirectory(Graphic)

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_TESTS_NAMES} PARENT_SCOPE)
