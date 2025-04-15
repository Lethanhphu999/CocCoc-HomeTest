#include "Command.h"


ICommand::ICommand(const typeCommand& typeCommand,
    const Point& point)
: _typeCommand(typeCommand),
_point(point) {

}

std::shared_ptr<ICommand> ICommand::Create(const typeCommand& type,
    const Point& point) {
        using Type = typeCommand;
        switch (type)
        {
        case Type::MOVE_TO:
            return std::make_shared<MoveCommand>(type, point);
            break;
        case Type::LINE_TO:
            return std::make_shared<LineCommand>(type, point);
            break;
        case Type::SPECIAL:
            return std::make_shared<SpecialCommad>(type, point);
            break;    
        default:
            throw("NOT FOUND TYPE COMMAND!!!");
            break;
        }
}

Point ICommand::getPoint() const {
    return _point;
}

MoveCommand::MoveCommand(const typeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void MoveCommand::Exec(std::shared_ptr<IMap> map) {
    map->MoveTo({getPoint()});
}


LineCommand::LineCommand(const typeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void LineCommand::Exec(std::shared_ptr<IMap> map) {
    map->LineTo({getPoint()});
}


SpecialCommad::SpecialCommad(const typeCommand& typeCommand,
    const Point& point) : ICommand (typeCommand, point) {

}

void SpecialCommad::Exec(std::shared_ptr<IMap> map) {
    map->HandleSpecialAction();
}


