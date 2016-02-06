#include "Command.hpp"

namespace SFGame
{

Command::Command(std::function<void(SceneNode&)>&& action, CommandCategory&& category)
{
    this->Action = action;
    this->Category = category;
}

Command::Command() :
    Action([](const SceneNode&)->void{}), Category(CommandCategory::eNone)
{
}

}
