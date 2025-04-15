#pragma once

#include "pch.h"
#include "CommandController.h"
#include "Map.h"

class Map;
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
    std::unique_ptr<Map> _map;
};
