#include "Position.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(Position, ConstructorDefaultsToZero) {
	Position pos;
	ASSERT_EQ(pos.getX(), 0);
	ASSERT_EQ(pos.getY(), 0);
}
