##
# Find for required libraries
##
macro( FindRequiredLibraries )

set(THREADS_PREFER_PTHREAD_FLAG ON)

# Workaround for ubuntu
set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules/)

find_package(Threads REQUIRED)
find_package(Boost 1.59 REQUIRED system program_options)
find_package(SFML  2.3  REQUIRED system window graphics network audio)
find_package(X11   1.6  REQUIRED)
find_package(GTest 1.7 REQUIRED)

set(EXTERNAL_LIBRARIES
  Threads::Threads
  m
  ${SFML_LIBRARIES}
  ${Boost_LIBRARIES}
  ${X11_LIBRARIES}
)

endmacro( FindRequiredLibraries )
