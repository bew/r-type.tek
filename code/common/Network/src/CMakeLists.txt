cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES ASocket.cpp NetworkBuffer.cpp NetworkSelect.cpp SocketException.cpp ASocketTCP.cpp ASocketUDP.cpp SockAddr.cpp ClientTCP.cpp ServerTCP.cpp ClientUDP.cpp ServerUDP.cpp AClient.cpp AServer.cpp)

if(UNIX)
    set(LIB_SOURCES ${LIB_SOURCES} SocketLinuxTCP.cpp SocketLinuxUDP.cpp)
elseif(WIN32)
    set(LIB_SOURCES ${LIB_SOURCES} SocketWindowsTCP.cpp SocketWindowsUDP.cpp)
    set(LIB_DEPENDENCIES ${LIB_DEPENDENCIES} ws2_32)
else()
    message(ERROR "Unsupported plateform")
endif()

set(LIB_DEPENDENCIES Logs)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

copy(${LIB_NAME} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})