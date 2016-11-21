AddStaticModule( utils
  FPS.cpp
  PeriodicTimer.cpp
  Gason.cpp
  ConfigParser.cpp
  Constants.hpp
  Units.hpp
)

AddTestSuite( utils_tests
  tests/UnitsSystemTests.cpp
  tests/ConfigParserTests.cpp
  tests/FPSTests.cpp
  tests/PeriodicTimerTests.cpp
)
