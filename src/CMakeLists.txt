file(GLOB_RECURSE EXEC_SRC
     "*.h"
     "*.cpp"
     )

find_package(CURL REQUIRED)
include_directories(${CURL_LIBRARIES})

find_package(Curses REQUIRED)
include_directories(${CURSES_LIBRARIES})

set(PANEL_LIBRARIES panel)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${spotifycli_SOURCE_DIR})

add_executable(spotifycli ${EXEC_SRC})

target_link_libraries(spotifycli ${CURL_LIBRARIES} ${CURSES_LIBRARIES} ${PANEL_LIBRARIES})