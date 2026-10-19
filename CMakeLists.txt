cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

project(UltimateParentalControls VERSION 1.0.0)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# manual dependency wrangling
# mfl is great but the cmakelists.txt really wants it to be installed and whatever
# so just going to compile it in with the rest of the mod lol
CPMAddPackage(
    NAME mfl
    GITHUB_REPOSITORY cpp-niel/mfl
    GIT_TAG 7ef9f07
    DOWNLOAD_ONLY YES
)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    ${mfl_SOURCE_DIR}/src/**.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${mfl_SOURCE_DIR}/include ${mfl_SOURCE_DIR}/src)

# Set up dependencies, resources, and link Geode.
setup_geode_mod(${PROJECT_NAME})
