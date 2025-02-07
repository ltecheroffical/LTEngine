# GUI Examples
if (NOT LTENGINE_DISABLE_GLFW)
    add_subdirectory(physics_simulation)
endif()

if (LTENGINE_BUILD_WITH_SDL)
    add_subdirectory(simple_scene)
endif()

add_subdirectory(thread_pool)
