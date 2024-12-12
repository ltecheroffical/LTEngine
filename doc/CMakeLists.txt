cmake_minimum_required(VERSION 3.16)

find_package(doxygen
    REQUIRED dot)

if (DOXYGEN_FOUND)
    # Check version
    if (DOXYGEN_VERSION VERSION_LESS 1.8.11)
        message(FATAL_ERROR "Doxygen version >= 1.8.11 is required")
    endif()

    set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})

    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)

    set(DOXYGEN_GENERATE_HTML YES)

    doxygen_add_docs(doc
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ALL
        COMMENT "Generate docs")
else()
    message(STATUS "Doxygen required to generate docs but not found. Skipping...")
endif()
