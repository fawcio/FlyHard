/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <iostream>
#include <cassert>

#include "game/Player.hpp"
#include "entities/PlayerAircraft.hpp"
#include "commands/CommandQueue.hpp"

namespace fly_hard
{

Player::Player()
{
	mKeyBinding[sf::Keyboard::Key::A] = Action::eMoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::eMoveRight;
	mKeyBinding[sf::Keyboard::Key::W] = Action::eAccelerate;
	mKeyBinding[sf::Keyboard::Key::S] = Action::eSlowDown;
	mKeyBinding[sf::Keyboard::Key::Space] = Action::eFirePrimary;
    mKeyBinding[sf::Keyboard::Key::RControl] = Action::eFireSecondary;

    mActionBinding[Action::eAccelerate] = Command {
            derivedAction<PlayerAircraft>(AircraftMover{-PlayerAircraft::cAccelerationValue, 0.}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };
    mActionBinding[Action::eSlowDown] = Command {
            derivedAction<PlayerAircraft>(AircraftMover{PlayerAircraft::cAccelerationValue, 0.}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };
    mActionBinding[Action::eMoveLeft] = Command {
            derivedAction<PlayerAircraft>(AircraftMover{0., -PlayerAircraft::cAccelerationValue}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };
    mActionBinding[Action::eMoveRight] = Command {
            derivedAction<PlayerAircraft>(AircraftMover{0., PlayerAircraft::cAccelerationValue}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };

    mActionBinding[Action::eFirePrimary] = Command {
            derivedAction<PlayerAircraft>(AircraftShooter{AircraftShooter::Type::eMinigun}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };
    mActionBinding[Action::eFireSecondary] = Command {
            derivedAction<PlayerAircraft>(AircraftShooter{AircraftShooter::Type::eRocket}),
            CommandCategory {CommandCategory::ePlayerAircraft}
    };
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
