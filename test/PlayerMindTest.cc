#include "PlayerMind.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(PlayerMind, ConstructorWorksInASimpleCase) {

	// Player Body
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};
	PlayerBody self(blood, position, unit_info);	

	PlayerMind mind(self);

	ASSERT_EQ(mind.getUnitId(), self.getUnitId());
}

TEST(PlayerMind, EqaulityOperatorOnlyChecksBodyEquality) {

	// Player Body
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};
	PlayerBody self(blood, position, unit_info);	

	PlayerMind mind1(self);
	PlayerMind mind2(self);

	ASSERT_EQ(mind1, mind2);
}