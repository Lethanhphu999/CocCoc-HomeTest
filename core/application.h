#pragma once

#include "commands/command_controller.h"

class CommandController;
class IMap;

class Application {
public:
    explicit Application(const std::string& path);
    ~Application() = default;
    void exec();
private:
    void start();
    void end();
private:
    std::string _path;
   
    std::unique_ptr<CommandController> _commandController;
    std::shared_ptr<IMap> _map;
};
