# -------------------------------------------------------------------

# List all the header files in the external directory
set(EXTERNAL_HEADERS
  # Dear ImGui
  imgui/imgui.h
  imgui/imconfig.h
  imgui/imgui_internal.h
  imgui/imstb_rectpack.h
  imgui/imstb_textedit.h
  imgui/imstb_truetype.h
  # ImGui-SFML
  ImGui-SFML/imgui-SFML.h
  ImGui-SFML/imconfig-SFML.h
  ImGui-SFML/imgui-SFML_export.h
  # ImGuiFileDialog
  ImGuiFileDialog/ImGuiFileDialog.h
  ImGuiFileDialog/ImGuiFileDialogConfig.h
)

# List all the source files in the external directory
set(EXTERNAL_SOURCES
  # Dear ImGui
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  # ImGui-SFML
  ImGui-SFML/imgui-SFML.cpp
  # ImGuiFileDialog
  ImGuiFileDialog/ImGuiFileDialog.cpp
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
