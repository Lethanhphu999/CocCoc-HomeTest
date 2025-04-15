#include "pch.h"

#include "CommandController.h"


CommandController::CommandController(const std::string& path)
: _path(path) {
    ParseCommands();
}

void CommandController::ParseCommands() {

}

void CommandController::ExecCommands(std::shared_ptr<IMap> map) {
    for (auto& command : _commands) {
        command->Exec(map);
    }
}

void CommandController::ExecSpecialCommad(std::shared_ptr<IMap> map) {
    if (_specialCommands.empty()) {
        std::cout << "----------NO SPECIAL COMMAND!!-------------\n";
        return;
    }

    for (auto& command : _specialCommands) {
        command->Exec(map);
    }
}







