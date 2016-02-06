#pragma once

namespace SFGame
{

struct CommandCategory
{
    enum value_t
    {
        eNone           = 0,
        eScene          = 1,
        ePlayerAircraft	= 2,
        eEnemyAircraft	= 4
    } value;

    explicit CommandCategory() : value(eNone) {}
    explicit CommandCategory(unsigned int val) : value(static_cast<value_t>(val)) {}

    explicit operator bool()
    {
        return ( this->value != eNone  );
    }
};

inline CommandCategory operator|(const CommandCategory left, CommandCategory right)
{
    return CommandCategory(left.value | right.value);
}

inline CommandCategory operator&(const CommandCategory left, CommandCategory right)
{
    return CommandCategory(left.value & right.value);
}

}
