#include "World.h"
#include "gtest/gtest.h"

using namespace Monarchy;

class WorldTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }
    World world;
    string team_name = "New Team Name";
    TeamId team_id = 3;
};

TEST_F(WorldTest, TeamsCanBeAddedToTheWorld) {
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    ASSERT_EQ(world.getTeam(team_id)->getName(), team_name);
    ASSERT_EQ(world.getTeam(team_id)->getId(), team_id);
}

TEST_F(WorldTest, NewUnitIdReturnsDifferentValues) {
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
}

TEST_F(WorldTest, NewTeamIdIncreasesIncrementally) {
    ASSERT_EQ(world.getNewTeamId(), 1);
    ASSERT_EQ(world.getNewTeamId(), 2);
    ASSERT_EQ(world.getNewTeamId(), 3);
}

TEST_F(WorldTest, WorldInitializesTeamLeadersWhenTheyAreAdded) {
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));

    ASSERT_EQ(world.getPlayerBodies().size(), 4);
    ASSERT_EQ(world.getPlayerMinds().size(), 4);
}
