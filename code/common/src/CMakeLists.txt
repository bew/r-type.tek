set(LIB_SOURCE)

# NETWORK sources
#------------------------------------

#add(LIB_SOURCE, network/my_file.cpp)

# BSON sources
#------------------------------------

add(LIB_SOURCE BSON/Document.cpp)
#add(LIB_SOURCE bson/file.cpp)

add_library(${RT_COMMON_NAME} ${LIB_SOURCE})
