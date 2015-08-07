#include "State.hpp"

namespace sfml_playground
{

State::State(StateStack &stack, Context context)
{
    (void) stack;
    (void) context;
}

void State::requestStackPush(StateID stateID)
{
    (void) stateID;
}

void State::requestStackPop()
{

}

void State::requestStackClear()
{

}

}
