#include "Application.h"

class Map;

Application::Application(const std::string& path)
: _commandController(std::make_shared<CommandController>(path)),
_map(std::make_shared<Map>(path)) {
}

void Application::Exec() {
    Start();
    _commandController->ExecCommands(_map);
    _commandController->ExecSpecialCommad(_map);
    End();
}

void Application::Start() {
    std::cout << "------------Start CocCoc-HomeTest-------------\n";

}
void Application::End() {
    std::cout << "------------End CocCoc-HomeTest---------------\n";
}



