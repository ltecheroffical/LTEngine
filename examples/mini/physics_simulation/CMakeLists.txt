project(physics_simulation_example LANGUAGES CXX)

file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${CXX_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE LTEngine)
