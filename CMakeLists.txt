cmake_minimum_required(VERSION 3.1)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_BINARY_DIR}/config.hpp"
)

include( cmake/cmake_defines.cmake )

CreateProject( SFML_Playground
  src/SFML_playground.cpp
)

add_subdirectory( src/entities )
add_subdirectory( src/game )
add_subdirectory( src/utils )
add_subdirectory( src/state_mgmt )

BuildProject( SFML_Playground )
