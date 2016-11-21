AddStaticModule( state_mgmt
  State.cpp
  Context.cpp
  StateIdentifiers.hpp
  StateStack.hpp
)

AddTestSuite( state_tests
  tests/StateTests.cpp
  tests/ContextTests.cpp
)
