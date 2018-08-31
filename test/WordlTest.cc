#include "World.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(World, TeamsCanBeAddedToTheWorld) {
	World world;
  string team_name = "New Team Name";
  TeamId team_id = 3;

  world.addTeam(std::make_unique<Team>(team_name, team_id));

 	ASSERT_EQ(world.getTeam(team_id)->getName(), team_name);
  ASSERT_EQ(world.getTeam(team_id)->getId(), team_id);

}

TEST(World, NewUnitIdReturnsDifferentValues) {
	World world;

  ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
  ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
  ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());

}

TEST(World, NewTeamIdIncreasesIncrementally) {
	World world;

  ASSERT_EQ(world.getNewTeamId(), 1);
  ASSERT_EQ(world.getNewTeamId(), 2);
  ASSERT_EQ(world.getNewTeamId(), 3);
}
