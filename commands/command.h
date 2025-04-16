#pragma once

#include "pch.h"
#include "data/map.h"

class Map;
struct Point;

enum class TypeCommand {
    MOVE_TO,
    LINE_TO,
    SPECIAL, 
};

class ICommand {
public:

    static std::shared_ptr<ICommand> Create(const TypeCommand& type,
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

