# -------------------------------------------------------------------

# Incorporating documentation generation into the main CMakeLists

find_package(Doxygen REQUIRED)

# Find all the public headers
get_target_property(MUSIC_SPECTRUM_PUBLIC_HEADER_DIR 
  MusicSpectrum INTERFACE_INCLUDE_DIRECTORIES
)

file(GLOB_RECURSE 
  MUSIC_SPECTRUM_PUBLIC_HEADERS ${MUSIC_SPECTRUM_PUBLIC_HEADER_DIR}/*.hpp
)

# This will be the main output of our command
set(DOXYGEN_INDEX_FILE 
  ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html
)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${MUSIC_SPECTRUM_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   MAIN_DEPENDENCY Doxyfile
                   COMMENT "Generating docs"
)

add_custom_target(Documentation ALL DEPENDS ${DOXYGEN_INDEX_FILE})

# -------------------------------------------------------------------
