#pragma once 

#include "commands/command.h"

class ICommand;

class CommandController {
public:
    CommandController();
    ~CommandController() = default;

    void prepare(std::vector<Command> commands);
    void execCommands(std::shared_ptr<IMap> map);
    void execSpecialCommands(std::shared_ptr<IMap> map);

private:    
    std::vector<std::unique_ptr<ICommand>> _commands;
    std::vector<std::unique_ptr<ICommand>> _specialCommands;


};