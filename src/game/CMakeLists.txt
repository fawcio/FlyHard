AddStaticModule( game
  Game.cpp
  World.cpp
  Player.cpp
)

AddTestSuite( game_tests
  tests/GameTests.cpp
  tests/PlayerTests.cpp
  tests/WorldTests.cpp
)
