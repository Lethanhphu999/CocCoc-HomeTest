#include "commands/command.h"

// Implementation of CreateCommand function
std::unique_ptr<ICommand> CreateCommand(const TypeCommand& type, const Point& point) {
    using Type = TypeCommand;
    switch (type) {
    case Type::MOVE_TO:
        return std::make_unique<MoveCommand>(type, point);
    case Type::LINE_TO:
        return std::make_unique<LineCommand>(type, point);
    case Type::SPECIAL:
        return std::make_unique<SpecialCommad>(type, point);
    default:
        return std::make_unique<MoveCommand>(TypeCommand::MOVE_TO, point);
    }
}

