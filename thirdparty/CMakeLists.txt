cmake_minimum_required(VERSION 3.16)

# OpenGL
if (LTENGINE_COMPONENT_OPENGL)
    add_subdirectory(glad)
    target_link_libraries(${PROJECT_NAME} PUBLIC glad)
endif()

# SDL
if (LTENGINE_COMPONENT_SDL)
    add_subdirectory(SDL)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL)
endif()

# Physics
if (LTENGINE_COMPONENT_PHYSICS_BOX2D)
    add_subdirectory(box2d)
    target_link_libraries(${PROJECT_NAME} PUBLIC box2d)
endif()

# STB Utilites
add_subdirectory(stb_image)
add_subdirectory(stb_truetype)
target_link_libraries(${PROJECT_NAME} PUBLIC stb_image stb_truetype)

# OpenSSL
find_package(OpenSSL REQUIRED) # Not in the repo as a submodule because OpenSSL is way to common place to manually include it

target_link_libraries(LTEngine PRIVATE OpenSSL::Crypto)
