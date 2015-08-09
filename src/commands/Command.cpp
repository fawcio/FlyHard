#include "Command.hpp"

namespace sfml_playground
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
