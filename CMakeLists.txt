cmake_minimum_required(VERSION 3.12) # CONFIGURE_DEPENDS is available in 3.12+
project(ray_pong_c C)

set(C_STANDARD C89)

if (UNIX)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

# set linker flags on Windows to void console in background in release (must be done before compiling raylib)
if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL Release)
    if (MINGW)
        add_link_options(-mwindows)
    endif()

    if(MSVC)
        add_link_options(/subsystem:windows /entry:mainCRTStartup)
    endif()
endif()

# RAYLIB ---------------
# Set this to the exact desired version, leave empty to use latest
set(RAYLIB_VERSION)

find_package(raylib ${RAYLIB_VERSION} QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    if(NOT RAYLIB_VERSION)
        set(RAYLIB_VERSION master)
    endif()

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/${RAYLIB_VERSION}.tar.gz
    )

    unset(RAYLIB_VERSION)

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied games

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

# END RAYLIB ---------------

# add source code
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.c" "src/game/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib)

