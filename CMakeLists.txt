#	Setup
cmake_minimum_required(VERSION 3.5.1)
project(spotifyclient)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(Spotify_Client_VERSION_MAJOR 0)
set(Spotify_Client_VERSION_MINOR 1)

add_compile_options(-Wall -std=c++11 -Wno-logical-op-parentheses -Wno-expansion-to-defined)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#	Compile Definitions
# add_compile_definitions(CLIENT_DEBUG)
# add_compile_definitions(DEBUG)	# Enables Socket.IO debug logging
# add_compile_definitions(LOCALTEST)

#	Boost
# find_package(Boost COMPONENTS filesystem system REQUIRED)
# find_package(Boost 1.69.0 REQUIRED COMPONENTS system date_time random) 
set(BOOST_INCLUDEDIR "../boost_1_69_0/")

#	Socket.io
include_directories(extern/socketio/src)
include(extern/socketio/CMakeLists.txt)

#	src
add_subdirectory(src)

#	Tests
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


