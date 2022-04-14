# 2021-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
# See license.md for details.

# Version 3.2 and upwards.
CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

# Setup versioning.
set(BUILD_MAJOR 0)
set(BUILD_MINOR 3)
set(BUILD_PATCH 1)
set(BUILD_VERSION "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH}")

# Specify version for this project.
project (tempora VERSION ${BUILD_VERSION})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
endif()

string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

# .
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Make sure libraries will be places beside executable.
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (MSVC)
    # warning level 4 and all warnings as errors
    #add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wunused-result)
endif()

# Collect source and header files.
file(GLOB_RECURSE TEMPORA_SRC
    ${PROJECT_SOURCE_DIR}/src/tempora/*.c
)
add_library(tempora ${TEMPORA_SRC})
target_include_directories(tempora PUBLIC
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
)
set_property(TARGET tempora PROPERTY C_STANDARD 17)