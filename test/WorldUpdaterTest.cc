#include "WorldUpdater.h"
#include "gtest/gtest.h"

using namespace Monarchy;

#define INITIAL_BLOOD_LEVEL 50
#define REPRODUCE_MAX_DIST 3
#define ARROW_MAX_DIST 5
#define SPEAR_MAX_DIST 2
#define ARROW_DAMAGE 5
#define SPEAR_DAMAGE 10

class WorldUpdaterTest : public ::testing::Test {
  protected:
    void SetUp() override {
        updater = new WorldUpdater(world);
        string team_name = "New Team Name";
        TeamId team_id = world.getNewTeamId();
        world.addTeam(std::make_unique<Team>(team_name, team_id));
        team_name = "New Second Team Name";
        team_id = world.getNewTeamId();
        world.addTeam(std::make_unique<Team>(team_name, team_id));
    }
    void TearDown() override {
        delete updater;
    }
    World world;
    WorldUpdater* updater;
    PlayerBody& getLeader1() {
        return world.getPlayerBodies().begin()->second;
    }
    PlayerBody& getLeader2() {
        return (world.getPlayerBodies().begin()++)->second;
    }
    void MovePlayerTo(UnitId playerUnitId, Position destination) {
        PlayerBody& player = world.getPlayerBody(playerUnitId);
        PlayerMovePtr move = nullptr;
        while(player.getPosition().x != destination.x) {
            Position nextMove (player.getPosition().x, player.getPosition().y);
            if(player.getPosition().x < destination.x) {
                nextMove.x += 1;
            } else {
                nextMove.x -= 1;
            }
            move= std::make_unique<PlayerWalk>(nextMove);
            updater->handleMove(move, player.getUnitId());
        }
        while(player.getPosition().y != destination.y) {
            Position nextMove (player.getPosition().x, player.getPosition().y);
            if(player.getPosition().y < destination.y)
                nextMove.y += 1;
            else
                nextMove.y -= 1;
            move= std::make_unique<PlayerWalk>(nextMove);
            updater->handleMove(move, player.getUnitId());
        }
    }
    PlayerBody& makeArcher1() {
        PlayerBody& leader1 = getLeader1();
        PlayerBody& leader2 = getLeader2();
        Position spawn_location(leader1.getPosition().x + 1, leader1.getPosition().y + 1);
        PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
        updater->handleMove(move, leader1.getUnitId());
        auto bodies = world.getPlayerBodies();
        for(auto it = bodies.begin(); it != bodies.end(); it++) {
            if(it->second.getUnitType() == UnitType::Archer)
                return it->second;
        }
    }
    PlayerBody& makeSpearman1() {
        PlayerBody& leader1 = getLeader1();
        PlayerBody& leader2 = getLeader2();
        Position spawn_location(leader2.getPosition().x - 1, leader2.getPosition().y - 1);
        PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Spearman, spawn_location);
        updater->handleMove(move, leader1.getUnitId());
        auto bodies = world.getPlayerBodies();
        for(auto it = bodies.begin(); it != bodies.end(); it++) {
            if(it->second.getUnitType() == UnitType::Spearman)
                return it->second;
        }
    }
};

TEST_F(WorldUpdaterTest, WorldUpdaterHandlesPlayerReproduction) {
    PlayerBody& leader1 = getLeader1();
    Position spawn_location(leader1.getPosition().x + 1, leader1.getPosition().y + 1);
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    updater->handleMove(move, leader1.getUnitId());
    ASSERT_NE(world.getGameState().getUnitIdOfPlayerAt(spawn_location), 0);
}

TEST_F(WorldUpdaterTest, WorldUpdaterHandlesPlayerWalk) {
    PlayerBody& leader1 = getLeader1();

    Position current_position = leader1.getPosition();
    Position desitnation1 (current_position.x, current_position.y + 1);

    PlayerMovePtr move = std::make_unique<PlayerWalk>(desitnation1);
    updater->handleMove(move, leader1.getUnitId());
    ASSERT_EQ(leader1.getPosition(), desitnation1);

    current_position = leader1.getPosition();
    Position desitnation2 (current_position.x + 1, current_position.y);
    move = std::make_unique<PlayerWalk>(desitnation2);
    updater->handleMove(move, leader1.getUnitId());

    ASSERT_EQ(leader1.getPosition(), desitnation2);
}

TEST_F(WorldUpdaterTest, WorldUpdaterHandlesArrowAttack) {
    PlayerBody& leader1 = getLeader1();
    PlayerBody& leader2 = getLeader2();
    PlayerBody& archer = makeArcher1();
    MovePlayerTo(archer.getUnitId(), Position(leader2.getPosition().x + 1, leader2.getPosition().y + 1 ));

    BloodLevel before_attack = leader2.getBlood();
    PlayerMovePtr move = std::make_unique<ArrowAttack>(leader2.getUnitId());
    updater->handleMove(move, archer.getUnitId());
    BloodLevel after_attack = leader2.getBlood();

    ASSERT_EQ(after_attack, before_attack - ARROW_DAMAGE);
}

TEST_F(WorldUpdaterTest, WorldUpdaterHandlesSpearAttack) {
    PlayerBody& leader1 = getLeader1();
    PlayerBody& leader2 = getLeader2();
    PlayerBody& spearman = makeSpearman1();
    MovePlayerTo(spearman.getUnitId(), Position(leader2.getPosition().x - 1, leader2.getPosition().y - 1));

    BloodLevel before_attack = leader2.getBlood();
    PlayerMovePtr move = std::make_unique<SpearAttack>(leader2.getUnitId());
    updater->handleMove(move, spearman.getUnitId());
    BloodLevel after_attack = leader2.getBlood();

    ASSERT_EQ(after_attack, before_attack - SPEAR_DAMAGE);
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfAnArcherTriesToReproduce) {
    PlayerBody& archer = makeArcher1();
    Position spawn_location = Position(archer.getPosition().x + 1, archer.getPosition().y );
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    ASSERT_THROW(updater->handleMove(move, archer.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfASpearmanTriesToReproduce) {
    PlayerBody& spearman = makeSpearman1();
    Position spawn_location = Position(spearman.getPosition().x + 1, spearman.getPosition().y );
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    ASSERT_THROW(updater->handleMove(move, spearman.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfSpawnLocationIsOccupied) {
    PlayerBody& leader = getLeader1();
    Position spawn_location = Position(leader.getPosition().x, leader.getPosition().y );
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfSpawnLocationIsTooFar) {
    PlayerBody& leader = getLeader1();
    Position spawn_location = Position(leader.getPosition().x + REPRODUCE_MAX_DIST, leader.getPosition().y + 1 );
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId());, MoveNotValid );
    spawn_location = Position(leader.getPosition().x + 1, leader.getPosition().y +  REPRODUCE_MAX_DIST );
    move = std::make_unique<PlayerReproduction>(UnitType::Archer, spawn_location);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfSpawnTypeIsLeader) {
    PlayerBody& leader = getLeader1();
    Position spawn_location = Position(leader.getPosition().x + 1, leader.getPosition().y + 1 );
    PlayerMovePtr move = std::make_unique<PlayerReproduction>(UnitType::Leader, spawn_location);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfWalkDestinationIsMoreThanOneBlockAway) {
    PlayerBody& leader = getLeader1();
    Position destination = Position(leader.getPosition().x + 1, leader.getPosition().y + 1 );
    PlayerMovePtr move = std::make_unique<PlayerWalk>(destination);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
    destination = Position(leader.getPosition().x + 2, leader.getPosition().y );
    move = std::make_unique<PlayerWalk>(destination);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
    destination = Position(leader.getPosition().x, leader.getPosition().y - 2);
    move = std::make_unique<PlayerWalk>(destination);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
    destination = Position(leader.getPosition().x + 1, leader.getPosition().y - 1);
    move = std::make_unique<PlayerWalk>(destination);
    ASSERT_THROW(updater->handleMove(move, leader.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfSpearAttackIsNotByASpearman) {
    PlayerBody& leader1 = getLeader1();
    PlayerBody& leader2 = getLeader2();
    PlayerBody& archer = makeArcher1();
    MovePlayerTo(archer.getUnitId(), Position(leader2.getPosition().x + 1, leader2.getPosition().y + 1 ));

    PlayerMovePtr move = std::make_unique<SpearAttack>(leader2.getUnitId());
    ASSERT_THROW(updater->handleMove(move, archer.getUnitId()), MoveNotValid );

    move = std::make_unique<SpearAttack>(archer.getUnitId());
    ASSERT_THROW(updater->handleMove(move, leader2.getUnitId()), MoveNotValid );
}

TEST_F(WorldUpdaterTest, ThrowsExceptionIfSpearmanIsTooFarFromTarget) {
    PlayerBody& leader1 = getLeader1();
    PlayerBody& leader2 = getLeader2();
    PlayerBody& spearman = makeSpearman1();

    MovePlayerTo(spearman.getUnitId(), Position(leader2.getPosition().x + SPEAR_MAX_DIST, leader2.getPosition().y + 1 ));
    PlayerMovePtr move = std::make_unique<SpearAttack>(leader2.getUnitId());
    ASSERT_THROW(updater->handleMove(move, spearman.getUnitId()), MoveNotValid );

    MovePlayerTo(spearman.getUnitId(), Position(leader2.getPosition().x + 1, leader2.getPosition().y + SPEAR_MAX_DIST ));
    move = std::make_unique<SpearAttack>(leader2.getUnitId());
    ASSERT_THROW(updater->handleMove(move, spearman.getUnitId()), MoveNotValid );
}
