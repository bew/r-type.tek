## **COMPILING**

#### **LINUX -> LINUX**
*You need cmake, make, and c/c++ compiler such as gcc and co*

First, go to the directory you want to build in.
For exemple,  
`mkdir project_root/build; cd project_root/build`

Then you must generate the project for make.  
`cmake -G "Unix Makefiles" ..`  

Then build the project:  
`cmake --build .`

To install to bin directory:  
`cmake --build . --target install`

*It doesn't work !*  
Be sure to replace `..` with path to project root.  
Be sure gcc is up to date.  
Else, maybe we fucked up something, no idea.

#### **LINUX -> WINDOWS**
*You need cmake, make, and a cross compiler such as mingw*

Please note that these instruction are only guideline, and may vary a lot depending
of your own system and configuration.
toolchain file are included as exemple.  
They may work on an archlinux based distribution. You would need the following packet:
community/mingw-w64-binutils 2.27-1 (mingw-w64-toolchain mingw-w64)
community/mingw-w64-crt 5.0.0-1 (mingw-w64-toolchain mingw-w64)
community/mingw-w64-gcc 6.2.1-1 (mingw-w64-toolchain mingw-w64)
community/mingw-w64-headers 5.0.0-1 (mingw-w64-toolchain mingw-w64)
community/mingw-w64-winpthreads 5.0.0-1 (mingw-w64-toolchain mingw-w64)

First choose a target plateform (see `toolchain` directory)

Then, go to the directory you want to build in.  
For exemple,  
`mkdir project_root/build; cd project_root/build`

Then you must generate the project for make.  
`cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/the-one-you-choosed -G "Unix Makefiles" ..`  

Then build the project:  
`cmake --build .`

To install to bin directory:  
`cmake --build . --target install`

*It doesn't work !*  
Be sure to replace `..` with path to project root.  
Be sure mingw is up to date. Also depending on your linux distribution, you may need to tweak cross compiler config.   
Also, you will need to provide your cross compiler specific dll (for libc, libstdc++ and pthread at least)   
Else, maybe we fucked up something, no idea.

#### **WINDOWS -> WINDOWS**
*You need cmake, and visual studio*

First, go to the directory you want to build in.  
For exemple,  
`mkdir project_root/build; cd project_root/build`

Then you must generate the project for micro$oft visual studio builder.  
It's been tested on VS14, no idea if it work with other versions.  
`cmake -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DBUILD_SHARED_LIBS=TRUE -G "Visual Studio 14" ..`  

Then build the project:  
`cmake --build .`

To install to bin directory:  
`cmake --build . --target install`

*It doesn't work !*  
Be sure to replace `..` with path to project root.  
Be sure cmake is up to date, and same for VS14. (Note `CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE` is recent)  
Else, maybe we fucked up something, no idea.

## **TEST**
