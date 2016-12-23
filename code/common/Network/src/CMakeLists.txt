cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCES ASocket.cpp NetworkBuffer.cpp NetworkSelect.cpp SocketException.cpp ASocketTCP.cpp ASocketUDP.cpp SockAddr.cpp ClientTCP.cpp ServerTCP.cpp ClientUDP.cpp ServerUDP.cpp AClient.cpp AServer.cpp)
set(LIB_DEPEDENCIES)

if(UNIX)
    set(LIB_SOURCES ${LIB_SOURCES} SocketLinuxTCP.cpp SocketLinuxUDP.cpp)
elseif(WIN32)
    set(LIB_SOURCES ${LIB_SOURCES} SocketWindowsTCP.cpp SocketWindowsUDP.cpp)
    set(LIB_DEPENDENCIES ${LIB_DEPENDENCIES} ws2_32)
else()
    message(ERROR "Unsupported plateform")
endif()

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )