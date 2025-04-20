#pragma once

#include "data/map.h"

class Map;
struct Point;

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

class ICommand {
public:

    static std::unique_ptr<ICommand> Create(const TypeCommand& type,
                                            const Point& point);
    virtual void exec(std::shared_ptr<IMap> map) const = 0;
    virtual ~ICommand() = default;

    Point getPoint() const {
        return _point;
    }

protected:
    ICommand(const TypeCommand& typeCommand,
        const Point& point);
        
    
private:
    TypeCommand _typeCommand;
    Point _point;
};

class MoveCommand : public ICommand {
public:
    MoveCommand(const TypeCommand& typeCommand,
                const Point& point);
    void exec(std::shared_ptr<IMap> map) const override;           
    
};

class LineCommand : public ICommand {
public:
    LineCommand(const TypeCommand& typeCommand,
                const Point& point);
    void exec(std::shared_ptr<IMap> map) const override;    
};


class SpecialCommad : public ICommand {
public:
    SpecialCommad(const TypeCommand& typeCommand,
                const Point& point);
    void exec(std::shared_ptr<IMap> map) const override;    
};

