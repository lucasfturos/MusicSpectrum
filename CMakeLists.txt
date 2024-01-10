cmake_minimum_required(VERSION 3.5)  # CMake version check

set(PROJECT_NAME                      # Define all project info
  MusicSpectrum 
  LANGUAGES CXX
  VERSION 1.0.0
)

project(${PROJECT_NAME})              # Create project "MusicSpectrum"

set(CMAKE_CXX_STANDARD 17)            # Enable c++11 standard

set(PROJECT_HEADER                    # Directory of all header file
  external/imgui.h
  external/imconfig.h
  external/imgui-SFML.h
  external/imconfig-SFML.h
  external/imgui_internal.h
  external/imstb_rectpack.h
  external/imstb_textedit.h
  external/imstb_truetype.h
  external/imgui-SFML_export.h
  src/music_espectro.hpp
  src/FFT/fft.hpp
  src/Spectrum/spectrum.hpp
)

set(PROJECT_SOURCE                    # Directory of all source file
  external/imgui.cpp
  external/imgui-SFML.cpp
  external/imgui_demo.cpp
  external/imgui_draw.cpp
  external/imgui_tables.cpp
  external/imgui_widgets.cpp
  src/FFT/fft.cpp
  src/Spectrum/waves_senoide.cpp
  src/Spectrum/waves_rect.cpp
  src/Spectrum/controller.cpp
  src/Spectrum/spectrum.cpp
  src/Spectrum/samples.cpp
  src/main.cpp
)

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
  -Wall -Wextra -Wpedantic -Werror -pedantic -g -Ofast 
)

# Add executable target with source and header files listed in PROJECT_HEADER and PROJECT_SOURCE variable
add_executable(${PROJECT_NAME} 
  ${PROJECT_HEADER} 
  ${PROJECT_SOURCE}
)

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME}
  PRIVATE src
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-graphics
  PRIVATE sfml-window
  PRIVATE sfml-system
  PRIVATE sfml-audio
)
