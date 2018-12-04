cmake_minimum_required(VERSION 3.5.1)

project(spotifyclient)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(Spotify_Client_VERSION_MAJOR 0)
set(Spotify_Client_VERSION_MINOR 1)

add_compile_options(-Wall -std=c++11 -Wno-logical-op-parentheses)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_definitions(DEBUG)
add_compile_definitions(LOCALTEST)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
set(spotify_api_include_dirs
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
include_directories(${spotify_api_include_dirs})
file(GLOB_RECURSE spotify_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_subdirectory(extern/googletest/)
enable_testing()
add_subdirectory(tests)


