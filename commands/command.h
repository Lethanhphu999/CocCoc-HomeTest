#pragma once

#include "data/map.h"

// Forward declarations
class IMap;
struct Point;
class ConfigurationAction;

enum class TypeCommand {
    MOVE_TO,
    LINE_TO,
    SPECIAL, 
};

struct Command {
    TypeCommand type;
    Point point;

    Command(TypeCommand t, Point p) : type(t), point(p) {}
    Command() : type(TypeCommand::MOVE_TO) {}
};

// Base command interface
class ICommand {
public:
    virtual void exec(std::shared_ptr<IMap> map) const = 0;
    virtual ~ICommand() = default;
    
    Point getPoint() const {
        return _point;
    }

protected:
    ICommand(const TypeCommand& typeCommand, const Point& point)
        : _typeCommand(typeCommand), _point(point) {}
    
private:
    TypeCommand _typeCommand;
    Point _point;
};

// CRTP base class for commands
template<typename Derived>
class CommandBase : public ICommand {
public:
    CommandBase(const TypeCommand& typeCommand, const Point& point)
        : ICommand(typeCommand, point) {}
    
    void exec(std::shared_ptr<IMap> map) const override {
        static_cast<const Derived*>(this)->execImpl(map);
    }

protected:
    virtual void execImpl(std::shared_ptr<IMap> map) const = 0;
};

// Factory method declaration
std::unique_ptr<ICommand> CreateCommand(const TypeCommand& type, const Point& point);

// Move command implementation
class MoveCommand : public CommandBase<MoveCommand> {
public:
    MoveCommand(const TypeCommand& typeCommand, const Point& point)
        : CommandBase<MoveCommand>(typeCommand, point) {}
    
    void execImpl(std::shared_ptr<IMap> map) const override {
        map->moveTo(ConfigurationAction(getPoint()));
    }
};

// Line command implementation
class LineCommand : public CommandBase<LineCommand> {
public:
    LineCommand(const TypeCommand& typeCommand, const Point& point)
        : CommandBase<LineCommand>(typeCommand, point) {}
    
    void execImpl(std::shared_ptr<IMap> map) const override {
        map->lineTo(ConfigurationAction(getPoint()));
    }
};

// Special command implementation
class SpecialCommad : public CommandBase<SpecialCommad> {
public:
    SpecialCommad(const TypeCommand& typeCommand, const Point& point)
        : CommandBase<SpecialCommad>(typeCommand, point) {}
    
    void execImpl(std::shared_ptr<IMap> map) const override {
        map->handleSpecialAction();
    }
};


