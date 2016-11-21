##
# Create and set up basic project properties
##
macro( CreateProject project_name version_major version_minor version_revison)

project( ${project_name} )

set( PROJECT_NAME ${project_name} )
set( PROJECT_VERSION_MAJOR ${version_major} )
set( PROJECT_VERSION_MINOR ${version_minor} )
set( PROJECT_VERSION_REVISION ${version_revison} )

if( NOT ${CMAKE_BUILD_TYPE} OR ${CMAKE_BUILD_TYPE} STREQUAL "" )
  set( CMAKE_BUILD_TYPE Debug )
endif()

if( ${CMAKE_BUILD_TYPE} MATCHES Debug )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -fstack-protector-all -march=native -std=c++1y -Wall -Wextra -pedantic -Werror" )
elseif( ${CMAKE_BUILD_TYPE} MATCHES Release )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -std=c++1y -Wall -Wextra -pedantic -Werror")
else()
  message(ERROR "Unsupported build type ${CMAKE_BUILD_TYPE}")
endif()

message( STATUS "Configuring project ${project_name} for ${CMAKE_BUILD_TYPE} build" )

configure_file(
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_BINARY_DIR}/src/config.hpp"
)

include_directories( src )
include_directories( ${PROJECT_BINARY_DIR}/src )

endmacro( CreateProject )







##
# Create the game executable
##
macro( CreateGameExecutable exec_name )
message( STATUS "Creating GAME_EXECUTABLE ${exec_name}" )

add_executable( ${exec_name}
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_link_libraries( ${exec_name}
  -Wl,--start-group ${PROJECT_MODULES} -Wl,--end-group
  ${EXTERNAL_LIBRARIES}
)

set_target_properties( ${exec_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

endmacro( CreateGameExecutable )







##
# Add a static project module.
##
macro( AddStaticModule module_name )
message( STATUS "Adding MODULE ${module_name}" )
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
# Add a test suite.
##
macro( AddTestSuite suite_name )

message( STATUS "Adding TEST_SUITE ${suite_name}" )
set( PROJECT_TEST_SUITES ${PROJECT_MODULES} ${suite_name} PARENT_SCOPE)

add_executable( ${suite_name}
  ${CMAKE_SOURCE_DIR}/src/tests.cpp
  ${ARGN}
)

target_include_directories( ${suite_name} PUBLIC
  ./
  ${GTEST_INCLUDE_DIRS}
)

target_link_libraries( ${suite_name}
  ${GTEST_LIBRARIES}
  pthread
)

set_target_properties( ${suite_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests )

endmacro( AddTestSuite )







##
# Create a symbolic link to Resources.
##
macro( SymLinkResources )
message( STATUS "Creating a symlink to Resources in build directory ${CMAKE_SOURCE_DIR}/Resources -> ${CMAKE_BINARY_DIR}" )
execute_process(
  COMMAND ln -sf ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
endmacro( SymLinkResources )
