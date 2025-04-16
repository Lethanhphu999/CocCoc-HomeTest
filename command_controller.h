#pragma once 

#include "command.h"

class ICommand;

class CommandController {
public:
    CommandController(const std::string& path);
    ~CommandController() = default;

    void execCommands(std::shared_ptr<IMap> map);
    void execSpecialCommands(std::shared_ptr<IMap> map);

private:    
    void parseCommands();
    const std::string _path;
    std::vector<std::shared_ptr<ICommand>> _commands;
    std::vector<std::shared_ptr<ICommand>> _specialCommands;


};