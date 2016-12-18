find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
	if(NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()

    # Configure the doxygen config file with current settings:
    configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(doc ${TARGET_ALL}
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            COMMENT "Generating API doc for ${PROJECT_NAME}" VERBATIM)

    set(INSTALL_DOC_DIR ${CMAKE_SOURCE_DIR}/doc)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION ${INSTALL_DOC_DIR} COMPONENT doc)
endif()