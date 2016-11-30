project("common")

set(PUBLIC_INCLUDE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	)

include_directories(
	${PUBLIC_INCLUDE}
	)

add_subdirectory("src")

# For all target having the common lib as dependancy,
# add some include path.
target_include_directories(${RT_COMMON_NAME}
	PUBLIC ${PUBLIC_INCLUDE}
	)
