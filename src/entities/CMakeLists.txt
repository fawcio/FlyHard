AddStaticModule( entities
  Entity.cpp
  PlayerAircraft.cpp
  SceneNode.cpp
  Landscape.cpp
)

AddTestSuite( entities_tests
  tests/EntityTests.cpp
  tests/LandscapeTests.cpp
  tests/PlayerAircraftTests.cpp
  tests/SceneNodeTests.cpp
)
