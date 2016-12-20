set(LIB_SOURCE ASocket.cpp NetworkBuffer.cpp NetworkSelect.cpp SocketException.cpp ASocketTCP.cpp ASocketUDP.cpp SockAddr.cpp ClientTCP.cpp ServerTCP.cpp ClientUDP.cpp ServerUDP.cpp AClient.cpp AServer.cpp)
set(LIB_DEPEDENCIES)

if(UNIX)
    set(LIB_SOURCE ${LIB_SOURCE} SocketLinuxTCP.cpp SocketLinuxUDP.cpp)
elseif(WIN32)
    set(LIB_SOURCE ${LIB_SOURCE} SocketWindowsTCP.cpp SocketWindowsUDP.cpp)
else()
    message(ERROR "Unsupported plateform")
endif()

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
add_library(${LIB_TEST_NAME} SHARED ${LIB_SOURCE})

IF (WIN32)
    set(LIB_DEPENDENCIES ${LIB_DEPENDENCIES} ws2_32)
ENDIF (WIN32)

target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_link_libraries(${LIB_TEST_NAME} ${LIB_DEPENDENCIES})
install(TARGETS ${LIB_TEST_NAME} DESTINATION bin/test/lib)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
target_include_directories(${LIB_TEST_NAME} PUBLIC ${LIB_INCLUDE})
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)
set(RT_COMMON_TESTS_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)
add_custom_command(TARGET ${LIB_NAME}
                   POST_BUILD
                   COMMAND  ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
                   )
