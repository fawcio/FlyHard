/*
 * Player.hpp
 *
 *  Created on: 20 cze 2015
 *      Author: slawek
 */

#ifndef SRC_GAME_PLAYER_HPP_
#define SRC_GAME_PLAYER_HPP_

#include <SFML/System.hpp>
#include <map>

#include "utils/CommandQueue.hpp"

namespace sfml_playground
{

class Player
{
public:
	enum class Action
	{
		eMoveLeft,
		eMoveRight,
		eFirePrimary,
		eFireSecondary
	};

public:
	Player();
	virtual ~Player() = default;

	void handleEvent(const sf::Event& event, std::shared_ptr<CommandQueue> commnands);

	void handleRealTimeInput(std::shared_ptr<CommandQueue> commands);

	void assignKey(Action action, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	static bool isRealtimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action>	mKeyBinding;
	std::map<Action, Command>			mActionBinding;
};

}

#endif /* SRC_GAME_PLAYER_HPP_ */
