#include "PlayerMind.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(PlayerMind, ConstructorWorksInASimpleCase) {

	UnitId self;
	PlayerMind mind(self);
}
