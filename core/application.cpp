#include "data/map.h"
#include "core/file_utilities.h"

#include "core/application.h"

class Map;
class SparseMap;

Application::Application(const std::string& path)
: _commandController(std::make_unique<CommandController>()),
_map(std::make_shared<Map>()), 
_path(path) {
}

void Application::exec() {
    start();
    auto resultReadRile = File::parseFile(_path);
    if (resultReadRile.result.isError()) {
        std::cout << resultReadRile.result.message;
        return;
    } else {
#ifdef DEBUG
        std::cout << "Read File oke!!!\n";
#endif
    }
    _map->init(resultReadRile.N);
    _map->print();
    _commandController->prepare(std::move(resultReadRile.commands));
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


