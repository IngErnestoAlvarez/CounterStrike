#include "prueba.h"

#include "gtest/gtest.h"

TEST(blaTest, test1) {
    Prueba pr;

    EXPECT_EQ(pr.foo(), 1);
    EXPECT_TRUE(pr.foo() != 0);
}
