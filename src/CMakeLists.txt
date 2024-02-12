# -------------------------------------------------------------------

# List all the header files in the src directory
set(SRC_HEADERS
  # FFT 
  FFT/fft.hpp
  # HUD
  HUD/hud.hpp
  # Object
  Object/cubo.hpp
  Object/cylinder.hpp
  Object/grid.hpp
  # OpenGL
  OpenGL/util.hpp
  OpenGL/shader.hpp
  # Spectrum 
  Spectrum/spectrum.hpp
  # Spectrum 3D
  Spectrum3D/spectrum3D.hpp
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
  # Object
  Object/cylinder.cpp
  Object/grid.cpp
  # OpenGL
  OpenGL/shader.cpp
  # Spectrum
  Spectrum/spectrum.cpp
  Spectrum/samples.cpp
  Spectrum/waves_rect.cpp
  Spectrum/waves_sine.cpp
  # Spectrum 3D
  Spectrum3D/opengl.cpp
  Spectrum3D/spectrum3D.cpp
  Spectrum3D/waves_sine.cpp
  # Render
  Render/plot.cpp
  Render/render.cpp
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
