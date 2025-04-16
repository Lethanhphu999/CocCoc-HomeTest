#pragma once

#include "pch.h"
#include "command_controller.h"
#include "map.h"

class IMap;
class CommandController;

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
