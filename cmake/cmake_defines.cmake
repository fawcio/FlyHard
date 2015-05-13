macro( SfmlAddStaticModule module_name )
set( PROJECT_MODULES ${PROJECT_MODULES} ${module_name} PARENT_SCOPE)

FOREACH(src_file ${ARGN})
  set(SRC_FILES ${SRC_FILES} ${src_file})
ENDFOREACH()

add_library( ${module_name} STATIC ${SRC_FILES} )

endmacro( SfmlAddStaticModule )
