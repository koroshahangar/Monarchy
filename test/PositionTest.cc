#include "Position.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(Position, ConstructorDefaultsToZero) {
    Position pos;
    ASSERT_EQ(pos.x, 0);
    ASSERT_EQ(pos.y, 0);
}

TEST(Position, EqualsOperatorWorks) {
    Position pos1(3,4);
    Position pos2(1,2);
    ASSERT_NE(pos1, pos2);
    pos2.x = 3;
    pos2.y = 4;
    ASSERT_EQ(pos1, pos2);
}