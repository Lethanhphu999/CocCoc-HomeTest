#pragma once

#include "pch.h"
#include "Map.h"


enum class typeCommand {
    MOVE_TO,
    LINE_TO,
    SPECIAL, 
};

struct Point {
    long long x;
    long long y;
};


class ICommand {
public:

    static std::shared_ptr<ICommand> Create(const typeCommand& type,
                                            const Point& point);
    virtual void Exec(std::shared_ptr<Map>& map) = 0;
protected:
    ICommand(const typeCommand& typeCommand,
        const Point& point);
    
private:
    typeCommand _typeCommand;
    Point _point;
};

class MoveCommand : public ICommand {
public:
    MoveCommand(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<Map>& map) override;           
    
};

class LineCommand : public ICommand {
public:
    LineCommand(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<Map>& map) override;    
};


class SpecialCommad : public ICommand {
public:
    SpecialCommad(const typeCommand& typeCommand,
                const Point& point);
    void Exec(std::shared_ptr<Map>& map) override;    
};

