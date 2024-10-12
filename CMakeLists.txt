project(LTEngine VERSION 0.1.0 LANGUAGES C)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} ${SOURCE_FILES})
endif()

add_subdirectory(thirdparty)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
