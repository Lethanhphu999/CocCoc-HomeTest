#include "commands/command.h"


ICommand::ICommand(const TypeCommand& typeCommand,
    const Point& point)
: _typeCommand(typeCommand),
_point(point) {

}

std::unique_ptr<ICommand> ICommand::Create(const TypeCommand& type,
    const Point& point) {
        using Type = TypeCommand;
        switch (type) {
        case Type::MOVE_TO:
            return std::make_unique<MoveCommand>(type, point);
            break;
        case Type::LINE_TO:
            return std::make_unique<LineCommand>(type, point);
            break;
        case Type::SPECIAL:
            return std::make_unique<SpecialCommad>(type, point);
            break;    
        default:
            throw("NOT FOUND TYPE COMMAND!!!");
            break;
        }
}


MoveCommand::MoveCommand(const TypeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void MoveCommand::exec(std::shared_ptr<IMap> map) const {
    map->moveTo({getPoint()});
}


LineCommand::LineCommand(const TypeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void LineCommand::exec(std::shared_ptr<IMap> map) const {
    map->lineTo({getPoint()});
}


SpecialCommad::SpecialCommad(const TypeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void SpecialCommad::exec(std::shared_ptr<IMap> map) const {
    map->handleSpecialAction();
}


