#include "WorldUpdater.h"
#include "gtest/gtest.h"

using namespace Monarchy;

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
    PlayerBody& makeArcher1() {
        PlayerBody& leader1 = getLeader1();
        PlayerBody& leader2 = getLeader2();
        Position spawn_location(leader2.getPosition().x - 2, leader2.getPosition().y - 2);
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
    Position spawn_location(3,3);
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

    BloodLevel before_attack = leader2.getBlood();

    PlayerMovePtr move = std::make_unique<ArrowAttack>(leader2.getUnitId());
    updater->handleMove(move, archer.getUnitId());

    BloodLevel after_attack = leader2.getBlood();

    ASSERT_TRUE(after_attack < before_attack);

}

TEST_F(WorldUpdaterTest, WorldUpdaterHandlesSpearAttack) {
    PlayerBody& leader1 = getLeader1();
    PlayerBody& leader2 = getLeader2();
    PlayerBody& spearman = makeSpearman1();

    BloodLevel before_attack = leader2.getBlood();
    PlayerMovePtr move = std::make_unique<SpearAttack>(leader2.getUnitId());
    updater->handleMove(move, spearman.getUnitId());

    BloodLevel after_attack = leader2.getBlood();

    ASSERT_EQ(after_attack, before_attack - SPEAR_DAMAGE);

}
