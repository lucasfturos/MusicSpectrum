# -------------------------------------------------------------------

# List all the header files in the external directory
set(EXTERNAL_HEADERS
  imgui.h
  imconfig.h
  imconfig-SFML.h
  imgui-SFML.h
  imgui_internal.h
  imstb_rectpack.h
  imstb_textedit.h
  imstb_truetype.h
  imgui-SFML_export.h
  tinyfiledialogs.h
)

# List all the source files in the external directory
set(EXTERNAL_SOURCES
  imgui.cpp
  imgui-SFML.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_tables.cpp
  imgui_widgets.cpp
  tinyfiledialogs.cpp
)

# Apply the compile flags to each source file in the external directory
foreach(SOURCE_FILE ${EXTERNAL_SOURCES})
  set_source_files_properties(${SOURCE_FILE} 
    PROPERTIES COMPILE_FLAGS -w
  )
endforeach()

# Create a library from the external sources and headers
add_library(external_lib 
  ${EXTERNAL_HEADERS}
  ${EXTERNAL_SOURCES}
)

# Include the external directory for header files
target_include_directories(external_lib 
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

# -------------------------------------------------------------------
