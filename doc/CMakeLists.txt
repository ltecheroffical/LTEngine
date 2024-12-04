find_package(doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})

    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)

    set(DOXYGEN_GENERATE_HTML YES)

    
doxygen_add_docs(doc
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ALL
    COMMENT "Generate docs")
endif()
