cmake_minimum_required(VERSION 3.5.1)

project(spotifycli)

set(Spotify_cli_VERSION_MAJOR 0)
set(Spotify_cli_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(src)

# target_link_libraries(spotifycli)


