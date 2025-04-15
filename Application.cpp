#include "Application.h"

Application::Application(const std::string& path)
: _commandController(std::make_shared<CommandController>(path)),
_map(std::make_unique<Map>(path)) {
}

void Application::Exec() {
    Start();

    End();
}

void Application::Start() {
    std::cout << "------------Start CocCoc-HomeTest-------------\n";

}
void Application::End() {
    std::cout << "------------End CocCoc-HomeTest---------------\n";
}

