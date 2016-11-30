# this is a static library for all generators
set(RT_GEN_COMMON_NAME gen_helper)
add_subdirectory("helpers")

# theses are the generators
add_subdirectory("levels")
#add_subdirectory("boss")
#add_subdirectory("somethingelse")
