#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System.hpp>

#include "State.hpp"

class State;

namespace sfml_playground
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

#endif // STATESTACK_HPP
