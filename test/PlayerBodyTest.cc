#include "PlayerBody.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(PlayerBody, ConstructorWorksInASimpleCase) {
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	PlayerBody pb(blood, position, unit_type, unit_id);	
}
