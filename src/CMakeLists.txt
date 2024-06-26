# -------------------------------------------------------------------

# List all the header files in the src directory
set(SRC_HEADERS
  # FFT 
  FFT/fft.hpp
  # HUD
  HUD/hud.hpp
  # Objects
  Objects/MobiusStrip/mobius_strip.cpp
  Objects/Plane/plane.hpp
  # Render
  Render/render.hpp
  # Sample
  Sample/sample.hpp
  # Shader
  Shader/shader.hpp
  # Spectrum 
  Spectrum/spectrum.hpp
  # Spectrum 3D
  Spectrum3D/spectrum3D.hpp
  # Timer
  Timer/timer.hpp
)

# List all the source files in the src directory
set(SRC_SOURCES
  # FFT
  FFT/fft.cpp
  # HUD
  HUD/hud.cpp
  HUD/ui.cpp
  HUD/events.cpp
  # Objects
  Objects/MobiusStrip/mobius_strip.cpp
  Objects/Plane/plane.cpp
  # Render
  Render/plot.cpp
  Render/render.cpp
  # Sample
  Sample/sample.cpp
  # Shader
  Shader/shader.cpp
  # Spectrum
  Spectrum/spectrum.cpp
  Spectrum/waves_rect.cpp
  Spectrum/waves_sine.cpp
  # Spectrum 3D
  Spectrum3D/setup.cpp
  Spectrum3D/spectrum3D.cpp
  Spectrum3D/waves_sine.cpp
  # Timer
  Timer/timer.cpp
  # Main
  main.cpp
)

# Find OpenGL libraries and their derivatives
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

# Find Threads library
find_package(Threads REQUIRED)

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
  # Threads
  PRIVATE Threads::Threads
  # SFML
  PRIVATE sfml-graphics
  PRIVATE sfml-window
  PRIVATE sfml-system
  PRIVATE sfml-audio
  # OpenGL
  PRIVATE glm::glm
  PRIVATE GLEW::GLEW
  PRIVATE ${CMAKE_DL_LIBS}
  PRIVATE ${OPENGL_LIBRARIES}
)

# -------------------------------------------------------------------
