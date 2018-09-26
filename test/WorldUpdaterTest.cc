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

TEST(WorldUpdater, WorldUpdaterHandlesArrowAttack) {
    World world;
    WorldUpdater updater(world);

    string team_name = "New Team Name";
    TeamId team_id = world.getNewTeamId();
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    PlayerBody& body1 = world.getPlayerBodies().begin()->second;

    team_name = "New Second Team Name";
    team_id = world.getNewTeamId();
    world.addTeam(std::make_unique<Team>(team_name, team_id));

    PlayerBody& body2 = (world.getPlayerBodies().begin()++)->second;

    while(abs(body2.getPosition().x - body1.getPosition().x) > 1) {
        Position destination;
        if(body2.getPosition().x > body1.getPosition().x)
            destination = Position(body2.getPosition().x -1, body2.getPosition().y);
        else
            destination = Position(body2.getPosition().x +1, body2.getPosition().y);
        PlayerMovePtr move = std::make_unique<PlayerWalk>(destination);
        updater.handleMove(move, body1.getUnitId());
    }
    while(abs(body2.getPosition().y - body1.getPosition().y) > 1) {
        Position destination;
        if(body2.getPosition().y > body1.getPosition().y)
            destination = Position(body2.getPosition().x, body2.getPosition().y -1);
        else
            destination = Position(body2.getPosition().x, body2.getPosition().y +1);
        PlayerMovePtr move = std::make_unique<PlayerWalk>(destination);
        updater.handleMove(move, body1.getUnitId());
    }

    BloodLevel before_attack = body2.getBlood();

    PlayerMovePtr move = std::make_unique<ArrowAttack>(body2.getUnitId());
    updater.handleMove(move, body1.getUnitId());

    BloodLevel after_attack = body2.getBlood();

    ASSERT_TRUE(after_attack < before_attack);
    //ASSERT_EQ(body2.getBloodLevel(), desitnation1);
    //
    //current_position = body.getPosition();
    //Position desitnation2 (current_position.x + 1, current_position.y);
    //
    //move = std::make_unique<PlayerWalk>(desitnation2);
    //
    //updater.handleMove(move, body.getUnitId());
    //
    //ASSERT_EQ(body.getPosition(), desitnation2);

}
