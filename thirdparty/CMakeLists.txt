cmake_minimum_required(VERSION 3.16)

# Windowing
if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(SDL) # Oof, this takes a while to compile
endif()

if (NOT LTENGINE_DISABLE_GLFW)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(glfw)
endif()

# GPU Graphics
if (LTENGINE_BUILD_WITH_VULKAN)
    add_subdirectory(vkbootstrap)
endif()
add_subdirectory(glad)

# Math
add_subdirectory(glm)

# Physics
add_subdirectory(box2d)

# Audio
cmake_policy(SET CMP0175 OLD)
add_subdirectory(soloud)

# STB Utilites
add_subdirectory(stb_image)
add_subdirectory(stb_truetype)

# OpenSSL
find_package(OpenSSL REQUIRED)
if (NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found")
endif()

# Linking
if (LTENGINE_BUILD_WITH_SDL)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        # Windowing
        SDL3
    )
endif()

if (NOT LTENGINE_DISABLE_GLFW)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        # Windowing
        glfw
    )
endif()

if (LTENGINE_BUILD_WITH_VULKAN)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        #GPU Graphics
        vk-bootstrap::vk-bootstrap
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC
    # GPU Graphics
    glad
    bgfx

    # Math
    glm::glm

    # Physics
    box2d

    # Audio
    soloud

    # STB Utilities
    stb_image
    stb_truetype

    # OpenSSL
    OpenSSL::SSL
    OpenSSL::Crypto
)
