#pragma once

#include <SFML/System.hpp>

#include "State.hpp"

class State;

namespace SFGame
{

class StateStack : private sf::NonCopyable
{
public:

    explicit StateStack() = default;
    virtual ~StateStack() = default;

	enum class Action
	{
		ePush,
		ePop,
		eClear
	};
};

}
