#include "PlayerList.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace Monarchy;

TEST(PlayerList, PlayersBodiesCanBeAdded) {
	PlayerList list;

	// Player Body
	BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};

	PlayerBody body_copy1(blood, position, unit_info);
	PlayerBody body_copy2(blood, position, unit_info);

	list.addPlayerBody(PlayerBody(blood, position, unit_info));

	ASSERT_EQ(body_copy1, list.getPlayerBody(body_copy1.getUnitId()));

	PlayerList list2;
	list2.addPlayerBody(body_copy2);
	ASSERT_EQ(body_copy1, list.getPlayerBody(body_copy1.getUnitId()));
}
