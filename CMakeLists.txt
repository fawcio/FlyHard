cmake_minimum_required( VERSION 3.0 )
project( SFML_Playground )

include( cmake/cmake_defines.cmake )

if( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -march=native -std=c++11")
elseif( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -std=c++11")
endif()

include_directories( ./src )

add_subdirectory( src/entities )
add_subdirectory( src/game )
add_subdirectory( src/utils )

add_executable( SFML_Playground 
  src/SFML_playground.cpp
)

target_link_libraries( SFML_Playground
  -Wl,--start-group ${PROJECT_MODULES} -Wl,--end-group
  rt
  pthread
  boost_system
  sfml-system
  sfml-window
  sfml-graphics
)
