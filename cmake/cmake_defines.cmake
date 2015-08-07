##
# Create and set up basic project properties
##
macro( CreateProject project_name version_major version_minor project_main_src_file)

project( ${project_name} )

set( PROJECT_NAME ${project_name} )
set( PROJECT_VERSION_MAJOR ${version_major} )
set( PROJECT_VERSION_MINOR ${version_minor} )

if( NOT ${CMAKE_BUILD_TYPE} OR ${CMAKE_BUILD_TYPE} STREQUAL "" )
  set( CMAKE_BUILD_TYPE Debug )
endif()

if( ${CMAKE_BUILD_TYPE} MATCHES Debug )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -fstack-protector-all -march=native -std=c++11 -Wall -Wextra -pedantic -Werror" )
elseif( ${CMAKE_BUILD_TYPE} MATCHES Release )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -std=c++11 -Wall -Wextra -pedantic -Werror")
else()
  message(ERROR "Unsupported build type ${CMAKE_BUILD_TYPE}")
endif()

message( STATUS "Configuring project ${project_name} for ${CMAKE_BUILD_TYPE} build" )

configure_file(
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_BINARY_DIR}/config.hpp"
)

include_directories( src )

add_executable( ${project_name} ${project_main_src_file} )

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
  set( SRC_FILES ${SRC_FILES} ${src_file} )
ENDFOREACH()

add_library( ${module_name} STATIC ${SRC_FILES} )

endmacro( AddStaticModule )





##
# Add a collection of header files.
##
macro( AddHeaderFiles target_name )

FOREACH(hdr_file ${ARGN})
  set( header_files ${header_files} ${hdr_file})
ENDFOREACH()

add_custom_target( ${target_name} SOURCES ${header_files} )

endmacro( AddHeaderFiles )







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
