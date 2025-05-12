cmake_minimum_required(VERSION 3.16)

# Physics
if (LTCORE_COMPONENT_PHYSICS_BOX2D)
    add_subdirectory(box2d)
    target_link_libraries(${PROJECT_NAME} PUBLIC box2d)
endif()

# STB Utilites
add_subdirectory(stb_image)
add_subdirectory(stb_truetype)

# OpenSSL
find_package(OpenSSL REQUIRED)

target_link_libraries(LTCore PRIVATE OpenSSL::Crypto)

# Linking
target_link_libraries(${PROJECT_NAME} PUBLIC
    # STB Utilities
    stb_image
    stb_truetype
)
