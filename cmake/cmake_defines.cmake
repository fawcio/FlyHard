##
# Create and set up basic project properties
##
macro( CreateProject project_name project_main_src_file)

project( ${project_name} )

if( NOT ${CMAKE_BUILD_TYPE} OR ${CMAKE_BUILD_TYPE} STREQUAL "" )
  set( CMAKE_BUILD_TYPE Debug )
endif()

message( STATUS "Configuring project ${project_name} for ${CMAKE_BUILD_TYPE} build" )

if( ${CMAKE_BUILD_TYPE} MATCHES Debug )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -fstack-protector-all -march=native -std=c++11 -Wall -Wextra -pedantic -Werror" )
elseif( ${CMAKE_BUILD_TYPE} MATCHES Release )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -std=c++11 -Wall -Wextra -pedantic -Werror")
endif()

FindRequiredLibraries()

include_directories( src )

add_executable( ${project_name} ${project_main_src_file} )

SymLinkResources()

endmacro( CreateProject )







##
# Finish set up of a project
##
macro( BuildProject project_name )
message( STATUS "Linking modules with project ${project_name}" )

target_link_libraries( ${project_name}
  -Wl,--start-group ${PROJECT_MODULES} -Wl,--end-group
  ${EXTERNAL_LIBRARIES}
)

endmacro( BuildProject )






##
# Add a static project module.
##
macro( AddStaticModule module_name )
message( STATUS "Adding static module ${module_name}" )
set( PROJECT_MODULES ${PROJECT_MODULES} ${module_name} PARENT_SCOPE)

FOREACH(src_file ${ARGN})
  set(SRC_FILES ${SRC_FILES} ${src_file})
ENDFOREACH()

add_library( ${module_name} STATIC ${SRC_FILES} )

endmacro( AddStaticModule )







##
# Find for required libraries
##
macro( FindRequiredLibraries )

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost 1.55 REQUIRED system)
find_package(SFML  2.3  REQUIRED system window graphics network audio)
find_package(X11   1.6  REQUIRED)

set(EXTERNAL_LIBRARIES
  Threads::Threads
  ${SFML_LIBRARIES}
  ${Boost_LIBRARIES}
  ${X11_LIBRARIES}
)

endmacro( FindRequiredLibraries )







##
# Create a symbolic link to Resources.
##
macro( SymLinkResources )
message( STATUS "Creating a symlink to Resources in build directory ${CMAKE_BINARY_DIR}" )
execute_process(
  COMMAND /usr/bin/ln -sf ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
endmacro( SymLinkResources )
