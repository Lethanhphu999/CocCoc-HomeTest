#pragma once

#include "pch.h"
#include "CommandController.h"
#include "Map.h"

class IMap;
class CommandController;

class Application {
public:
    explicit Application(const std::string& path);
    ~Application() = default;
    void Exec();
private:
    void Start();
    void End();
private:
    std::string _path;
   
    std::shared_ptr<CommandController> _commandController;
    std::shared_ptr<IMap> _map;
};
