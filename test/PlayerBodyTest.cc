#include "PlayerBody.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(PlayerBody, ConstructorWorksInASimpleCase) {
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};
	PlayerBody pb(blood, position, unit_info);	
}
