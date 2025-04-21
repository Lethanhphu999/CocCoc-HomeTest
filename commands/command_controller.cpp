#include "commands/command_controller.h"
#include "commands/command.h"

CommandController::CommandController() {

}

void CommandController::prepare(std::vector<Command> commands) {
    _commands.reserve(commands.size());
    for(const auto& command : commands) {
        _commands.emplace_back(std::move(
            CreateCommand(command.type, command.point)));
    }
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







