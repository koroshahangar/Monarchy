#include "Position.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(Position, ConstructorDefaultsToZero) {
	Position pos;
	ASSERT_EQ(pos.x, 0);
	ASSERT_EQ(pos.y, 0);
}
