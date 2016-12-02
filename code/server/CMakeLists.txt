set(CL_INCLUDE)
add(CL_INCLUDE include ${RT_COMMON_INCLUDE})

include_directories(${CL_INCLUDE})
add_subdirectory("src")
