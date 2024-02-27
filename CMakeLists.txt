# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)  # CMake version check

# Set policy to prefer GLVND when finding OpenGL
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# -------------------------------------------------------------------

set(PROJECT_NAME                      # Define all project info
  MusicSpectrum 
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "MusicSpectrum"

set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# List all the files
set(RESOURCES_DIRECTORY 
  "${CMAKE_SOURCE_DIR}/assets"
)

# Copy the entire assets directory to the binary directory during build
file(COPY ${RESOURCES_DIRECTORY} 
  DESTINATION ${CMAKE_BINARY_DIR}
)

# Flags of compiling
add_compile_options(
  -Wall -Wextra -Wpedantic -Werror -pedantic -Wno-unknown-pragmas -g -Ofast 
)

# Add subdirectories for external and src
add_subdirectory(external)
add_subdirectory(src)

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
  ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html
)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${MUSIC_SPECTRUM_PUBLIC_HEADERS} ${DOXYFILE_IN}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   MAIN_DEPENDENCY ${DOXYFILE_IN}
                   COMMENT "Generating docs"
)

add_custom_target(Documentation ALL DEPENDS ${DOXYGEN_INDEX_FILE})

# -------------------------------------------------------------------
