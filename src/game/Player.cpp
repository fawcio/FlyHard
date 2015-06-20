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

void Player::handleEvent(const sf::Event& event, std::shared_ptr<CommandQueue> commands)
{
	if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.Category.value = CommandCategory::ePlayerAircraft;
		output.Action = [] (SceneNode& node) {
			std::cout << node.getPosition().x << ','
					  << node.getPosition().y << '\n';
		};
		commands->push(std::move(output));
	}
}

void Player::handleRealTimeInput(std::shared_ptr<CommandQueue> commands)
{
	const float playerSpeed = 300.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Command moveLeft;
		moveLeft.Category.value = CommandCategory::ePlayerAircraft;
		moveLeft.Action = derivedAction<PlayerAircraft>(
				AircraftMover(-playerSpeed, 0.0f));
		commands->push(std::move(moveLeft));
	}
}

}
