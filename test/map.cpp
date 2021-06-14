#include "gtest/gtest.h"
#include "../include/map.h"

TEST(MapTests, loadedMapReturnsCorrectName) {
    Map map("../assets/maps/test_map.yaml");
    EXPECT_EQ("Test map", map.getName());
}

TEST(MapTests, loadedMapReturnsCorrectDimensions) {
    Map map("../assets/maps/test_map.yaml");
    EXPECT_EQ(4, map.getWidth());
    EXPECT_EQ(4, map.getHeight());
}
