#include <gtest/gtest.h>
#include "commands/command_controller.h"
#include "data/map.h"

class CommandControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        controller = std::make_unique<CommandController>();
        map = std::make_shared<Map>();
        map->init(5);
    }

    std::unique_ptr<CommandController> controller;
    std::shared_ptr<IMap> map;
};

TEST_F(CommandControllerTest, PrepareCommands) {
    std::vector<Command> commands;
    commands.push_back({TypeCommand::MOVE_TO, Point{2, 3}});
    commands.push_back({TypeCommand::LINE_TO, Point{4, 4}});
    commands.push_back({TypeCommand::SPECIAL, Point{1, 1}});
    
    controller->prepare(std::move(commands));
    // Verify commands were prepared correctly
}

TEST_F(CommandControllerTest, ExecuteCommands) {
    std::vector<Command> commands;
    commands.push_back({TypeCommand::MOVE_TO, Point{2, 3}});
    commands.push_back({TypeCommand::LINE_TO, Point{4, 4}});
    
    controller->prepare(std::move(commands));
    controller->execCommands(map);
    
    // Verify commands were executed correctly
    EXPECT_EQ(map->getCurrentPoint().x, 4);
    EXPECT_EQ(map->getCurrentPoint().y, 4);
}

TEST_F(CommandControllerTest, ExecuteSpecialCommands) {
    std::vector<Command> commands;
    commands.push_back({TypeCommand::SPECIAL, Point{2, 2}});
    
    controller->prepare(std::move(commands));
    controller->execSpecialCommands(map);
    
    // Verify special commands were executed correctly
}
