# Set global vars

project("common")
set(LIB_SOURCE)
set(LIB_DEPENDENCES)
# Add sources

add_subdirectory(fileSystemWatcher)
add_subdirectory(generatorUtils)

# Build common library
include_directories(${RT_COMMON_INCLUDE})
add_library(${RT_COMMON_NAME} SHARED ${LIB_SOURCE})
target_link_libraries(${RT_COMMON_NAME} ${LIB_DEPENDENCES})
install(TARGETS ${RT_COMMON_NAME} DESTINATION bin)

## For all target having the common lib as dependancy,
### add some include path.
target_include_directories(${RT_COMMON_NAME} PUBLIC ${RT_COMMON_INCLUDE})
set(RT_COMMON_INCLUDE ${RT_COMMON_INCLUDE} PARENT_SCOPE)
