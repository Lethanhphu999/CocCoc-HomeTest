#include "core/application.h"
#include "core/file_utilities.h"
#include "data/map.h"

// Forward declarations
class Map;
class SparseMap;

Application::Application(const std::string& path)
    : _path(path),
      _commandController(std::make_unique<CommandController>()),
      _map(std::make_shared<SparseMap>()) {
}

void Application::exec() {
    start();
    
    auto resultReadFile = File::parseFile(_path);
    if (resultReadFile.result.isError()) {
        std::cerr << resultReadFile.result.message;
        return;
    }
    
#ifdef DEBUG
    std::cout << "Read File successful!\n";
#endif

    _map->init(resultReadFile.N);
    _map->print();
    
    _commandController->prepare(std::move(resultReadFile.commands));
    _commandController->execCommands(_map);
    _commandController->execSpecialCommands(_map);
    
    _map->print();
    end();
}

void Application::start() {
    std::cout << "------------Start CocCoc-HomeTest-------------\n";
}

void Application::end() {
    std::cout << "------------End CocCoc-HomeTest---------------\n";
}


