#include "pch.h"

#include "command_controller.h"


CommandController::CommandController(const std::string& path)
: _path(path) {
    parseCommands();
}

void CommandController::parseCommands() {

}

void CommandController::execCommands(std::shared_ptr<IMap> map) {
    for (auto& command : _commands) {
        command->exec(map);
    }
}

void CommandController::execSpecialCommands(std::shared_ptr<IMap> map) {
    if (_specialCommands.empty()) {
        std::cout << "----------NO SPECIAL COMMAND!!-------------\n";
        return;
    }

    for (auto& command : _specialCommands) {
        command->exec(map);
    }
}







