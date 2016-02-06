#pragma once

#include <memory>

#include "Context.hpp"
#include "StateStack.hpp"
#include "StateIdentifiers.hpp"

class StateStack;

namespace SFGame
{

class State
{
public:
    using State_Ptr = std::unique_ptr<State>;
    struct Context {};

public:
    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update() = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(StateID stateID);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const { return mContext; }

private:
    StateStack* mStack;
    Context     mContext;
};

}
