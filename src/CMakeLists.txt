file(GLOB_RECURSE EXEC_SRC
     "*.h"
     "*.cpp"
     )

find_package(CURL REQUIRED)
include_directories(${CURL_LIBRARIES})

find_package(Curses REQUIRED)
include_directories(${CURSES_LIBRARIES})

find_package(OpenSSL REQUIRED)

include_directories(/usr/local/include/readline)

set(PANEL_LIBRARIES panel)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${spotifyclient_SOURCE_DIR})

file(GLOB_RECURSE LIB_SRC
     "api/*.h"
     "api/*.cpp"
     )

add_library(spotifyapilib ${LIB_SRC})
target_link_libraries(spotifyapilib ${CURL_LIBRARIES} ${CURSES_LIBRARIES} ${PANEL_LIBRARIES} sioclient OpenSSL::SSL readline)
# add_executable(spotifyclient spotifyclientlib)

add_executable(spotifyclient ${EXEC_SRC})

target_link_libraries(spotifyclient ${CURL_LIBRARIES} ${CURSES_LIBRARIES} ${PANEL_LIBRARIES} sioclient OpenSSL::SSL readline)
# target_link_libraries (spotifyclient LINK_PUBLIC spotifyclientlib)