AddStaticModule( entities
  Entity.cpp
  PlayerAircraft.cpp
  SceneNode.cpp
  Stars.cpp
)

AddTestSuite( entities_tests
  tests/EntityTests.cpp
  tests/SceneNodeTests.cpp
  tests/PlayerAircraftTests.cpp
  tests/StarsTests.cpp
)
