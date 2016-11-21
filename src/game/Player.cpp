#include <iostream>
#include <cassert>

#include "game/Player.hpp"
#include "entities/PlayerAircraft.hpp"
#include "commands/CommandQueue.hpp"

namespace SFGame
{

Player::Player()
{
	mKeyBinding[sf::Keyboard::Key::A] = Action::eMoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::eMoveRight;
	mKeyBinding[sf::Keyboard::Key::W] = Action::eAccelerate;
	mKeyBinding[sf::Keyboard::Key::S] = Action::eSlowDown;
	mKeyBinding[sf::Keyboard::Key::Space] = Action::eFirePrimary;
	mKeyBinding[sf::Keyboard::Key::LControl] = Action::eFireSecondary;

    mActionBinding[Action::eMoveLeft] = Command { derivedAction<PlayerAircraft>(AircraftMover{-PlayerAircraft::cAccelerationValue}),
										CommandCategory {CommandCategory::ePlayerAircraft} };
    mActionBinding[Action::eMoveRight] = Command { derivedAction<PlayerAircraft>(AircraftMover{PlayerAircraft::cAccelerationValue}),
										 CommandCategory {CommandCategory::ePlayerAircraft} };
	mActionBinding[Action::eAccelerate] = Command { derivedAction<PlayerAircraft>(AircraftMover{PlayerAircraft::cAccelerationValue}),
										 CommandCategory {CommandCategory::ePlayerAircraft} };
	mActionBinding[Action::eSlowDown] = Command { derivedAction<PlayerAircraft>(AircraftMover{PlayerAircraft::cAccelerationValue}),
										 CommandCategory {CommandCategory::ePlayerAircraft} };
}

void Player::handleEvent(const sf::Event& event, std::shared_ptr<CommandQueue> commands)
{
	if (commands)
	{
		if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::P)
		{
			Command output;
			output.Category.value = CommandCategory::ePlayerAircraft;
			output.Action = [] (SceneNode& node) {
				std::cerr << node.getPosition().x << ','
						  << node.getPosition().y << '\n';
			};
			commands->push(std::move(output));
		}
	}
}

void Player::handleRealTimeInput(std::shared_ptr<CommandQueue> commands)
{
	if (commands)
	{
		for (auto pair : mKeyBinding)
		{
			if (sf::Keyboard::isKeyPressed(pair.first))
			{
				commands->push(mActionBinding[pair.second]);
			}
		}
	}
}

}
