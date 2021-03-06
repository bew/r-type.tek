cmake_minimum_required(VERSION 3.1)

SET(CROSS_COMPILE true)
SET(CMAKE_SYSTEM_NAME Windows)
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-cc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-c++)
SET(CMAKE_AR /usr/x86_64-w64-mingw32/bin/ar)
SET(CMAKE_RANLIB /usr/x86_64-w64-mingw32/bin/ranlib)
INCLUDE_DIRECTORIES(SYSTEM /usr/x86_64-w64-mingw32/include)
LINK_DIRECTORIES(/usr/w86_64-w64-mingw32/bin /usr/x86_64-w64-mingw32/lib)