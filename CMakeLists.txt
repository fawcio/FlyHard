cmake_minimum_required(VERSION 3.1)

include( cmake/cmake_defines.cmake )
include( cmake/external_libraries.cmake )

FindRequiredLibraries()

CreateProject( SFML_Playground 0 1 3
  src/SFML_playground.cpp
)

add_subdirectory( src/entities )
add_subdirectory( src/game )
add_subdirectory( src/utils )
add_subdirectory( src/state_mgmt )
add_subdirectory( src/resource_mgmt)
add_subdirectory( src/commands )

BuildProject( SFML_Playground )

SymLinkResources()
