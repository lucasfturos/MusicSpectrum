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

# Set icon
set(ICON_FILE "${CMAKE_SOURCE_DIR}/assets/img/icon/favicon.ico")

# Copy the entire assets directory to the binary directory during build
file(COPY ${RESOURCES_DIRECTORY} 
  DESTINATION ${CMAKE_BINARY_DIR}
)

# Flags of compiling
add_compile_options(
  -Wall -Wextra -Wpedantic -Werror -pedantic -Wno-unknown-pragmas -g -Ofast 
)

# Add subdirectories for docs, external, src and tests
add_subdirectory(docs)
add_subdirectory(external)
add_subdirectory(src)

# Add the option to enable DEB package generation
option(ENABLE_DEB_PACKAGE "Enable DEB package generation" OFF)

# If the DEB package generation option is enabled, configure the DEB generator
if(ENABLE_DEB_PACKAGE)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_NAME "Music-Spectrum")
  set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
  set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Music Spectrum - Audio Visualizer")
  set(CPACK_PACKAGE_DESCRIPTION
  "Music Spectrum é um aplicativo que permite visualizar o espectro de frequência de arquivos de áudio em tempo real. O programa utiliza a transformada de Fourier rápida (FFT) para calcular o espectro de frequência e a fórmula de Euler para gerar visualizações vibrantes e interativas.")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lucas Turos <@lucasfturos>")
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/lucasfturos/MusicSpectrum/")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsfml-dev, libglew-dev, libglm-dev, mesa-common-dev, libgl1-mesa-dev, doxygen")

  include(CPack)
endif()

# -------------------------------------------------------------------
