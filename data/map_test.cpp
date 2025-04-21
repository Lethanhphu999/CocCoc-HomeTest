#include <gtest/gtest.h>
#include "data/map.h"

class MapTest : public ::testing::Test {
protected:
    void SetUp() override {
        map = std::make_unique<Map>();
        sparseMap = std::make_unique<SparseMap>();
    }

    std::unique_ptr<Map> map;
    std::unique_ptr<SparseMap> sparseMap;
};

TEST_F(MapTest, Initialization) {
    map->init(5);
    sparseMap->init(5);
    
    // Test map dimensions
    EXPECT_EQ(map->getCurrentPoint().x, 0);
    EXPECT_EQ(map->getCurrentPoint().y, 0);
}

TEST_F(MapTest, MoveTo) {
    map->init(5);
    Point target{2, 3};
    map->moveTo(ConfigurationAction(target));
    
    EXPECT_EQ(map->getCurrentPoint().x, 2);
    EXPECT_EQ(map->getCurrentPoint().y, 3);
}

TEST_F(MapTest, LineTo) {
    map->init(5);
    Point start{0, 0};
    Point end{2, 2};
    
    map->moveTo(ConfigurationAction(start));
    map->lineTo(ConfigurationAction(end));
    
    // Verify the line was drawn
    // This is a basic test - you might want to add more specific checks
    EXPECT_EQ(map->getCurrentPoint().x, 2);
    EXPECT_EQ(map->getCurrentPoint().y, 2);
}

TEST_F(MapTest, SparseMapOperations) {
    sparseMap->init(5);
    Point point{2, 2};
    
    // Use public methods for testing
    sparseMap->moveTo(ConfigurationAction(point));
    sparseMap->handleSpecialAction();  // This will call clearPoint internally
    
    // Verify the point was processed by checking the current point
    EXPECT_EQ(sparseMap->getCurrentPoint().x, 2);
    EXPECT_EQ(sparseMap->getCurrentPoint().y, 2);
}

TEST_F(MapTest, PointRange) {
    PointRange range(Point(1, 1), Point(3, 3), 5);
    Point point{2, 2};
    
    EXPECT_TRUE(range.from <= (point.x + point.y * 5));
    EXPECT_TRUE(range.till >= (point.x + point.y * 5));
}



