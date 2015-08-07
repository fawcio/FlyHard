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
