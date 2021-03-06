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

TEST_F(WorldTest, TeamsCanBeAddedToTheWorldAndRetrieved) {
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    ASSERT_EQ(world.getTeam(team_id)->getName(), team_name);
    ASSERT_EQ(world.getTeam(team_id)->getId(), team_id);
}

TEST_F(WorldTest, GetNewUnitIdReturnsDifferentValuesEachTimeItIsCalled) {
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
    ASSERT_NE(world.getNewUnitId(), world.getNewUnitId());
}

TEST_F(WorldTest, NewTeamIdIncreasesIncrementally) {
    ASSERT_EQ(world.getNewTeamId(), 1);
    ASSERT_EQ(world.getNewTeamId(), 2);
    ASSERT_EQ(world.getNewTeamId(), 3);
}

TEST_F(WorldTest, WorldInitializesTeamLeadersWhenTeamsAreAdded) {
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));
    world.addTeam(std::make_unique<Team>(team_name, world.getNewTeamId()));

    ASSERT_EQ(world.getPlayerBodies().size(), 4);
    ASSERT_EQ(world.getPlayerMinds().size(), 4);
}

TEST_F(WorldTest, AddingTeamWithExistingTeamIdThrowsException) {
    TeamId team_id = world.getNewTeamId();
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    string new_team_name = "A different name";
    ASSERT_THROW(world.addTeam(std::make_unique<Team>(new_team_name, team_id)), TeamAlreadyExists );
}

TEST_F(WorldTest, TryingToGetTeamWithInvalidTeamIdThrowsException) {
    TeamId invalid_team_id = world.getNewTeamId();
    // No team is added to the world
    ASSERT_THROW(world.getTeam(invalid_team_id), TeamNotFound );
}
