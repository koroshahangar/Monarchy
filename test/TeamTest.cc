#include "Team.h"
#include "PlayerList.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(Team, TeamReturnsAPlayerMindWhichCanBePassedToPlayerList) {
	Team team(std::string("MyTeam"), 2);

  BloodLevel blood = 15;
	Position position(10, 15);
	UnitType unit_type = UnitType::Leader;
	UnitId unit_id = 5;
	TeamId team_id = 1;
	UnitInfo unit_info {unit_id, unit_type, team_id};

	PlayerBody body(blood, position, unit_info);

  PlayerList list;
  list.addPlayerBody(body);
  list.addPlayerMind(team.getMindFor(body));

 	ASSERT_EQ(list.getPlayerMind(unit_id)->getUnitId(), list.getPlayerBody(unit_id).getUnitId());

}
