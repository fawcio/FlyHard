AddStaticModule( commands
  Command.cpp
  CommandQueue.cpp
  CommandCategory.hpp
)

AddTestSuite( commands_tests
  tests/CommandTests.cpp
  tests/CommandQueueTests.cpp
)
