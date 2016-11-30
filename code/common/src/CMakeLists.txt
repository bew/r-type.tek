set(LIB_SOURCE)

# NETWORK sources
#------------------------------------

add(LIB_SOURCE Network/src/ASocket.cpp)
add(LIB_SOURCE Network/src/NetworkBuffer.cpp)
add(LIB_SOURCE Network/src/NetworkSelect.cpp)
add(LIB_SOURCE Network/src/SocketException.cpp)

# BSON sources
#------------------------------------

add(LIB_SOURCE bson/some.cpp)

add_library(${RT_COMMON_NAME} ${LIB_SOURCE})
