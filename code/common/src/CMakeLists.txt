set(LIB_SOURCE)

# NETWORK sources
#------------------------------------

#add(LIB_SOURCE, network/my_file.cpp)

# BSON sources
#------------------------------------

add(LIB_SOURCE bson/some.cpp
        Network/src/ASocket.cpp
        Network/src/NetworkBuffer.cpp
        Network/src/NetworkSelect.cpp
        Network/src/SocketException.cpp)
#add(LIB_SOURCE bson/file.cpp)

add_library(${RT_COMMON_NAME} ${LIB_SOURCE})
