#include "WorldUpdater.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(WorldUpdater, WorldUpdaterHandlesPlayerReproduction) {
    World world;
    WorldUpdater updater(world);

    string team_name = "New Team Name";
    TeamId team_id = world.getNewTeamId();
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    PlayerBody& leader = world.getPlayerBodies().begin()->second;
    Position spawn_location(3,3);

    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);

    updater.handleMove(move, leader.getUnitId());

    ASSERT_NE(world.getGameState().getUnitIdOfPlayerAt(spawn_location), 0);
}

TEST(WorldUpdater, WorldUpdaterHandlesPlayerWalk) {
    World world;
    WorldUpdater updater(world);

    string team_name = "New Team Name";
    TeamId team_id = world.getNewTeamId();
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    PlayerBody& body = world.getPlayerBodies().begin()->second;

    Position current_position = body.getPosition();
    Position desitnation1 (current_position.x, current_position.y + 1);

    PlayerMovePtr move = std::make_unique<PlayerWalk>(desitnation1);

    updater.handleMove(move, body.getUnitId());

    ASSERT_EQ(body.getPosition(), desitnation1);

    current_position = body.getPosition();
    Position desitnation2 (current_position.x + 1, current_position.y);

    move = std::make_unique<PlayerWalk>(desitnation2);

    updater.handleMove(move, body.getUnitId());

    ASSERT_EQ(body.getPosition(), desitnation2);

}
