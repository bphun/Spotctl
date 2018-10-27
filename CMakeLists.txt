cmake_minimum_required(VERSION 3.5.1)

project(spotifyclient)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(Spotify_Client_VERSION_MAJOR 0)
set(Spotify_Client_VERSION_MINOR 1)

add_compile_options(-Wall -std=c++11 -Wno-logical-op-parentheses)
# set(CMAKE_SHARED_LINKER_FLAGS "-v")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# include(GNUInstallDirs)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# set(JSON_BuildTests OFF CACHE INTERNAL "")
# add_subdirectory(extern/json)
# add_library(nlohmann_json::nlohmann_json)

add_subdirectory(src)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest/googletest/include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest/googlemock/include)
# add_subdirectory(extern/googletest)

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


