# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)  # CMake version check

# Set policy to prefer GLVND when finding OpenGL (suppresses warning)
cmake_policy(SET CMP0072 NEW)

# -------------------------------------------------------------------

set(PROJECT_NAME                      # Define all project info
  MusicSpectrum 
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "MusicSpectrum"

set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# List all the music files
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

# -------------------------------------------------------------------
