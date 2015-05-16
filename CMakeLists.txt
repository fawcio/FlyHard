cmake_minimum_required(VERSION 3.0)

include( cmake/cmake_defines.cmake )

CreateProject( SFML_Playground
  src/SFML_playground.cpp
)

add_subdirectory( src/entities )
add_subdirectory( src/game )
add_subdirectory( src/utils )

BuildProject( SFML_Playground )
