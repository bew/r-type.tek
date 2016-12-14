# Set global vars

project("common")

set(RT_COMMON_NAMES)

# Add librariries
add_subdirectory(BSON)
add_subdirectory(LibraryLoader)
add_subdirectory(Network)

# Every sub libs must do more or less this
#set(LIB_NAME ...)
#set(LIB_SOURCE ...)
#set(LIB_DEPEDENDES ...)
#include_directories(...)
#add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
#add_library(${LIB_NAME}_test SHARED ${LIB_SOURCE})
#target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCES})
#install(TARGETS ${LIB_NAME}_test DESTINATION bin/test)
#target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
#target_include_directories(${LIB_NAME}_test PUBLIC ${LIB_INCLUDE})
#set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)

set(RT_COMMON_NAMES ${RT_COMMON_NAMES} PARENT_SCOPE)

message(STATUS "The common libraries names are : \n ${RT_COMMON_NAMES}\nIf something is missing, please check RT_COMMON_NAMES scope")
