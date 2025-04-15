#pragma once

#include "pch.h"
#include "Map.h"

class Map;
struct Point;

enum class typeCommand {
    MOVE_TO,
    LINE_TO,
    SPECIAL, 
};

class ICommand {
public:

    static std::shared_ptr<ICommand> Create(const typeCommand& type,
                                            const Point& point);
    virtual void Exec(std::shared_ptr<IMap> map) = 0;
    virtual ~ICommand() = default; 

protected:
    ICommand(const typeCommand& typeCommand,
        const Point& point);
    Point getPoint() const;    
    
private:
    typeCommand _typeCommand;
    Point _point;
};

class MoveCommand : public ICommand {
public:
    MoveCommand(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<IMap> map) override;           
    
};

class LineCommand : public ICommand {
public:
    LineCommand(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<IMap> map) override;    
};


class SpecialCommad : public ICommand {
public:
    SpecialCommad(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<IMap> map) override;    
};

