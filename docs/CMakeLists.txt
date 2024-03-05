# -------------------------------------------------------------------

find_package(Doxygen REQUIRED)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it on your system")
else()
    message(STATUS "Doxygen found.")

    file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.1/doxygen-awesome.css
    ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome.css)
    file(DOWNLOAD https://raw.githubusercontent.com/jothepro/doxygen-awesome-css/v2.3.1/doxygen-awesome-sidebar-only.css
    ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-sidebar-only.css)

    if (NOT DOXYGEN_EXTRACT_ALL)
        set(DOXYGEN_EXTRACT_ALL YES)
    endif()
    if (NOT DOXYGEN_EXTRACT_PRIVATE)
        set(DOXYGEN_EXTRACT_PRIVATE YES)
    endif()
    if (NOT DOXYGEN_GENERATE_HTML)
        set(DOXYGEN_GENERATE_HTML YES)
    endif()
    if (NOT DOXYGEN_OUTPUT_LANGUAGE)
        set(DOXYGEN_OUTPUT_LANGUAGE Brazilian)
    endif()
    if (NOT DOXYGEN_HTML_OUTPUT)
        set(DOXYGEN_HTML_OUTPUT ${CMAKE_BINARY_DIR}/html)
    endif()
    if (NOT DOXYGEN_IMAGE_PATH)
        set(DOXYGEN_IMAGE_PATH ${CMAKE_BINARY_DIR})
    endif()
    if (NOT DOXYGEN_GENERATE_TREEVIEW)
        set(DOXYGEN_GENERATE_TREEVIEW YES)
    endif()
    if(NOT DOXYGEN_FULL_PATH_NAMES)
        set(DOXYGEN_FULL_PATH_NAMES YES)
    endif()
    if(NOT DOXYGEN_FILE_PATTERNS)
        set(DOXYGEN_FILE_PATTERNS *.cpp *.hpp)
    endif()
    if(NOT DOXYGEN_USE_MDFILE_AS_MAINPAGE)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
    endif()
    if(NOT DOXYGEN_RECURSIVE)
        set(DOXYGEN_RECURSIVE YES)
    endif()

    list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome.css)
    list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET ${PROJECT_SOURCE_DIR}/docs/doxygen-awesome-sidebar-only.css)

    doxygen_add_docs(documentation 
        ${PROJECT_SOURCE_DIR}/src 
        "${PROJECT_SOURCE_DIR}/README.md" 
        COMMENT "Generating documentation")
endif()

# -------------------------------------------------------------------