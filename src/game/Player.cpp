/*
 * Player.cpp
 *
 *  Created on: 20 cze 2015
 *      Author: slawek
 */

#include <iostream>

#include "game/Player.hpp"
#include "entities/PlayerAircraft.hpp"

namespace sfml_playground
{

Player::Player()
{
	mKeyBinding[sf::Keyboard::Key::A] = Action::eMoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::eMoveRight;
	mKeyBinding[sf::Keyboard::Key::Space] = Action::eFirePrimary;
	mKeyBinding[sf::Keyboard::Key::LControl] = Action::eFireSecondary;

	mActionBinding[Action::eMoveLeft] = Command { derivedAction<PlayerAircraft>(AircraftMover{-6.f}),
										CommandCategory {CommandCategory::ePlayerAircraft} };
	mActionBinding[Action::eMoveRight] = Command { derivedAction<PlayerAircraft>(AircraftMover{6.f}),
										 CommandCategory {CommandCategory::ePlayerAircraft} };
}

void Player::handleEvent(const sf::Event& event, std::shared_ptr<CommandQueue> commands)
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

void Player::handleRealTimeInput(std::shared_ptr<CommandQueue> commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands->push(mActionBinding[pair.second]);
		}
	}
}

bool Player::isRealtimeAction(Player::Action action)
{
	(void) action;
	return true;
}

}
