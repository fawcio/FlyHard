cmake_minimum_required(VERSION 3.0)

include( cmake/cmake_defines.cmake )

CreateProject( SFML_Playground
  src/SFML_playground.cpp
)

add_subdirectory( src/entities )
add_subdirectory( src/game )
add_subdirectory( src/utils )
add_subdirectory( src/state_mgmt )

target_link_libraries( SFML_Playground
  rt
  pthread
  boost_system
  sfml-system
  sfml-window
  sfml-graphics
  X11
)

BuildProject( SFML_Playground )
