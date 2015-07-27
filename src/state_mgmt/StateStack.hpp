#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System.hpp>

#include "State.hpp"

class StateStack : private sf::NonCopyable
{
public:
	enum class Action
	{
		ePush,
		ePop,
		eClear
	};

public:
	explicit StateStack();
};

#endif // STATESTACK_HPP
