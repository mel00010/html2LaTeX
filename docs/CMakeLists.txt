include(DoxygenTargets)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_doxygen(${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs-generated/man/man3 DESTINATION /usr/local/man)