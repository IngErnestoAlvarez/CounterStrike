#include "gtest/gtest.h"
#include "../include/configuration.h"

TEST(ConfigurationTests, configurationReturnsPort) {
    Configuration config("../config/config.yaml");
    EXPECT_EQ("8000", config.getPort());
}
