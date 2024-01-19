# -------------------------------------------------------------------

# List all the header files in the src directory
set(SRC_HEADERS
  # FFT 
  FFT/fft.hpp
  # HUD
  HUD/hud.hpp
  # Spectrum 
  Spectrum/spectrum.hpp
  # Render
  Render/render.hpp
)

# List all the source files in the src directory
set(SRC_SOURCES
  # FFT
  FFT/fft.cpp
  # HUD
  HUD/hud.cpp
  HUD/ui.cpp
  HUD/events.cpp
  # Spectrum
  Spectrum/spectrum.cpp
  Spectrum/samples.cpp
  Spectrum/waves_rect.cpp
  Spectrum/waves_senoide.cpp
  # Render
  Render/render.cpp
  # Main
  main.cpp
)

# Find OpenGL libraries
find_package(OpenGL REQUIRED)

# Add executable target with source and header files
add_executable(${PROJECT_NAME} 
  ${SRC_HEADERS} 
  ${SRC_SOURCES}
)

# Specifies include directories to use when compiling
target_include_directories(${PROJECT_NAME} 
  PRIVATE src
  PRIVATE ${OPENGL_INCLUDE_DIRS}
)

# Link external library to the main executable
target_link_libraries(${PROJECT_NAME} 
  PRIVATE external_lib
)

# Specify libraries or flags to use when linking
target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-graphics
  PRIVATE sfml-window
  PRIVATE sfml-system
  PRIVATE sfml-audio
  PRIVATE ${OPENGL_LIBRARIES}
)

# -------------------------------------------------------------------
