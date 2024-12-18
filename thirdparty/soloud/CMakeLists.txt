cmake_minimum_required(VERSION 3.16)
project(soloud LANGUAGES C CXX)


file(GLOB_RECURSE CXX_SOURCE_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/*.cpp)

file(GLOB_RECURSE CXX_BACKEND_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/backend/*.cpp)

file (GLOB_RECURSE CXX_TOOLS_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/tools/*.cpp)

# Remove unwanted files
list(REMOVE_ITEM CXX_SOURCE_FILES ${CXX_BACKEND_SOURCES})
list(REMOVE_ITEM CXX_SOURCE_FILES ${CXX_TOOLS_SOURCES})

# Add backends I want
if (LTENGINE_BUILD_WITH_SDL)
    list(APPEND CXX_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/backend/sdl2_static/soloud_sdl2_static.cpp)
endif()
list(APPEND CXX_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/soloud/src/backend/miniaudio/soloud_miniaudio.cpp)

if (NOT TARGET soloud)
    add_library(soloud ${CXX_SOURCE_FILES})

    if (LTENGINE_BUILD_WITH_SDL)
        target_compile_definitions(${PROJECT_NAME} PUBLIC WITH_SDL2_STATIC)
        if (NOT BUILD_SHARED_LIBS)
            add_library(SDL2 ALIAS SDL2-static)
        endif()

        target_link_libraries(${PROJECT_NAME} PUBLIC SDL2)
    endif()
    target_compile_definitions(${PROJECT_NAME} PUBLIC WITH_MINIAUDIO)


    set(UNIX_PLATFORMS Linux FreeBSD NetBSD OpenBSD Darwin)
    if (CMAKE_SYSTEM_NAME IN_LIST UNIX_PLATFORMS)
        # Miniaudio documentation (2.2) says that we need to add `-lpthread` and `-lm`
        target_link_libraries(${PROJECT_NAME} PRIVATE -lpthread -lm)
    endif()

    if (LINUX)
        target_link_libraries(${PROJECT_NAME} PRIVATE -ldl)
    endif()

    if (IOS)
        # We are on iOS
        # Miniaudio documentation (2.2) says that the app might not pass notarization without "MA_NO_RUNTIME_LINKING"
        # But this comes at the cost of adding more libraries:
        #   `-framework CoreFoundation -framework CoreAudio -framework AudioUnit`
        # That cost is worth it for iOS support
        target_compile_definitions(${PROJECT_NAME} PUBLIC MA_NO_RUNTIME_LINKING)
        target_link_libraries(${PROJECT_NAME} PUBLIC -framework CoreFoundation -framework CoreAudio -framework AudioUnit)
    endif()
endif()

target_include_directories(soloud PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/soloud/include)
