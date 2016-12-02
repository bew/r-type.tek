# this is a static library for all generators

#set(RT_GEN_COMMON_NAME gen_helper)
#add_subdirectory("helpers")

# This automatically add generators

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    if(${subdir} MATCHES generator_*)
        add_subdirectory(${subdir})
    endif()
endforeach()
