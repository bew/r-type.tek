set(CL_INCLUDE)
add(CL_INCLUDE include)

include_directories(${CL_INCLUDE} ${RT_COMMON_INCLUDES})
add_subdirectory("src")
