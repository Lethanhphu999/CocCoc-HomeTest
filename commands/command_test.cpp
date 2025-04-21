#include <gtest/gtest.h>
#include "commands/command.h"
#include "data/map.h"

class CommandTest : public ::testing::Test {
protected:
    void SetUp() override {
        map = std::make_shared<Map>();
        map->init(5);
    }

    std::shared_ptr<IMap> map;
};

TEST_F(CommandTest, CreateCommand) {
    Point point{2, 3};
    
    auto moveCommand = CreateCommand(TypeCommand::MOVE_TO, point);
    auto lineCommand = CreateCommand(TypeCommand::LINE_TO, point);
    auto specialCommand = CreateCommand(TypeCommand::SPECIAL, point);
    
    EXPECT_NE(moveCommand, nullptr);
    EXPECT_NE(lineCommand, nullptr);
    EXPECT_NE(specialCommand, nullptr);
}

TEST_F(CommandTest, MoveCommand) {
    Point start{0, 0};
    Point target{2, 3};
    
    map->moveTo(ConfigurationAction(start));
    auto command = CreateCommand(TypeCommand::MOVE_TO, target);
    command->exec(map);
    
    EXPECT_EQ(map->getCurrentPoint().x, 2);
    EXPECT_EQ(map->getCurrentPoint().y, 3);
}

TEST_F(CommandTest, LineCommand) {
    Point start{0, 0};
    Point end{2, 2};
    
    map->moveTo(ConfigurationAction(start));
    auto command = CreateCommand(TypeCommand::LINE_TO, end);
    command->exec(map);
    
    EXPECT_EQ(map->getCurrentPoint().x, 2);
    EXPECT_EQ(map->getCurrentPoint().y, 2);
}

TEST_F(CommandTest, SpecialCommand) {
    Point point{2, 2};
    auto command = CreateCommand(TypeCommand::SPECIAL, point);
    command->exec(map);
    
    // Verify special command execution
    // Add specific checks based on your special command implementation
}
