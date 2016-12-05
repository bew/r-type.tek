set(LIB_SOURCE)

# NETWORK sources
#------------------------------------

add(LIB_SOURCE Network/src/ASocket.cpp)
add(LIB_SOURCE Network/src/NetworkBuffer.cpp)
add(LIB_SOURCE Network/src/NetworkSelect.cpp)
add(LIB_SOURCE Network/src/SocketException.cpp)
add(LIB_SOURCE Network/src/ASocketTCP.cpp)
add(LIB_SOURCE Network/src/ASocketUDP.cpp)

if (WIN32)
    add(LIB_SOURCE Network/src/SocketWindowsTCP.cpp)
    add(LIB_SOURCE Network/src/SocketWindowsUDP.cpp)
ELSEIF (UNIX)
    add(LIB_SOURCE Network/src/SocketLinuxTCP.cpp)
ENDIF (WIN32)

# BSON sources
#------------------------------------

add(LIB_SOURCE bson/some.cpp)

add_library(${RT_COMMON_NAME} ${LIB_SOURCE})
