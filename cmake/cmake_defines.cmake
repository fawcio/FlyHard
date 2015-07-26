##
# Create and set up basic project properties
##
macro( CreateProject project_name project_main_src_file)

project( ${project_name} )

if( NOT ${CMAKE_BUILD_TYPE})
  set( CMAKE_BUILD_TYPE "Debug" )
endif()

if( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -fstack-protector-all -march=native -std=c++11 -Wall -Wextra -pedantic -Werror" )
elseif( ${CMAKE_BUILD_TYPE} MATCHES "Release" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -std=c++11 -Wall -Wextra -pedantic -Werror")
endif()

include_directories( ./src )

add_executable( ${project_name} ${project_main_src_file} )

endmacro( CreateProject )


##
# Finish set up of a project
##
macro( BuildProject project_name )

target_link_libraries( ${project_name}
  -Wl,--start-group ${PROJECT_MODULES} -Wl,--end-group
)

endmacro( BuildProject )


##
# Add a static project module.
##
macro( AddStaticModule module_name )
set( PROJECT_MODULES ${PROJECT_MODULES} ${module_name} PARENT_SCOPE)

FOREACH(src_file ${ARGN})
  set(SRC_FILES ${SRC_FILES} ${src_file})
ENDFOREACH()

add_library( ${module_name} STATIC ${SRC_FILES} )

endmacro( AddStaticModule )
