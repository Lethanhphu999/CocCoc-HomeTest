#pragma once 

#include "Command.h"

class ICommand;

class CommandController {
public:
    CommandController(const std::string& path);
    ~CommandController() = default;

    void ExecCommands(std::shared_ptr<IMap> map);
    void ExecSpecialCommad(std::shared_ptr<IMap> map);

private:    
    void ParseCommands();
    const std::string _path;
    std::vector<std::shared_ptr<ICommand>> _commands;
    std::vector<std::shared_ptr<ICommand>> _specialCommands;


};