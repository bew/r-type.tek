# this is a static library for all generators

#set(RT_GEN_COMMON_NAME gen_helper)
#add_subdirectory("helpers")

set(GENERATORS_DIST bin/generators)

# This automatically add generators
macro(SUBDIRLIST result_name curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            add(dirlist ${child})
        endif()
    endforeach()
    set(${result_name} ${dirlist})
endmacro()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    if(${subdir} MATCHES generator_*)
        add_subdirectory(${subdir})
    endif()
endforeach()
