#include "application.h"

class Map;

Application::Application(const std::string& path)
: _commandController(std::make_unique<CommandController>(path)),
_map(std::make_shared<Map>(path)) {
}

void Application::exec() {
    start();
    _commandController->execCommands(_map);
    _commandController->execSpecialCommands(_map);
    end();
}

void Application::start() {
    std::cout << "------------Start CocCoc-HomeTest-------------\n";

}
void Application::end() {
    std::cout << "------------End CocCoc-HomeTest---------------\n";
}



