/*
 * Player.hpp
 *
 *  Created on: 20 cze 2015
 *      Author: slawek
 */

#ifndef SRC_GAME_PLAYER_HPP_
#define SRC_GAME_PLAYER_HPP_

#include <SFML/System.hpp>

#include "utils/CommandQueue.hpp"

namespace sfml_playground
{

class Player
{
public:
	Player()			= default;
	virtual ~Player()	= default;

	void	handleEvent(const sf::Event& event, std::shared_ptr<CommandQueue> commnands);

	void	handleRealTimeInput(std::shared_ptr<CommandQueue> commands);
};

}

#endif /* SRC_GAME_PLAYER_HPP_ */
