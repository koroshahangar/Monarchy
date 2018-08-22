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

TEST(PlayerBody, OnlyTheUnitIdMattersToEqaulityOperator) {
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};
	PlayerBody body1(blood, position, unit_info);	

	blood = 9;
	position = Position(1, 3);
	unit_type = UnitType::Archer;
	unit_id = 5;
	team_id = 2;
	UnitInfo unit_info2 {unit_id, unit_type, team_id};
	PlayerBody body2(blood, position, unit_info2);

	blood = 9;
	position = Position(1, 3);
	unit_type = UnitType::Archer;
	unit_id = 1;
	team_id = 2;
	UnitInfo unit_info3 {unit_id, unit_type, team_id};
	PlayerBody body3(blood, position, unit_info3);	

	ASSERT_EQ(body1, body2);
	ASSERT_NE(body2, body3);
}
