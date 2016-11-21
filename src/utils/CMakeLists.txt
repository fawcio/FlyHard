AddStaticModule( utils
  FPS.cpp
  PeriodicTimer.cpp
  Gason.cpp
  ConfigParser.cpp
  Constants.hpp
  Units.hpp
)

add_executable( utils_tests
  tests/UtilsTestsMain.cpp
  tests/UnitsTests.cpp
)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries( utils_tests
  utils
  ${GTEST_LIBRARIES}
  pthread
)
