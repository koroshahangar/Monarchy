#include "PlayerList.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace Monarchy;

class PlayerListTest : public ::testing::Test {
  protected:
    PlayerListTest():
        body(blood, position, UnitInfo {unit_id, unit_type, team_id}) {
    }

    PlayerList list;
    BloodLevel blood {15};
    Position position {10, 15};
    UnitType unit_type = UnitType::Leader;
    UnitId unit_id = 5;
    TeamId team_id = 1;
    UnitInfo unit_info {unit_id, unit_type, team_id};
    PlayerBody body {blood, position, unit_info};
};

TEST_F(PlayerListTest, PlayersBodiesCanBeAddedAndRetrieved) {
    list.addPlayerBody(PlayerBody(blood, position, unit_info));
    ASSERT_EQ(body, list.getPlayerBody(unit_id));
}

TEST_F(PlayerListTest, PlayersMindsCanBeAddedAndRetrieved) {
    list.addPlayerBody(PlayerBody(blood, position, unit_info));
    PlayerMindPtr mind = std::make_unique<PlayerMind>(list.getPlayerBody(unit_id));
    list.addPlayerMind(std::move(mind));

    ASSERT_EQ(list.getPlayerMind(unit_id)->getUnitId(), list.getPlayerBody(unit_id).getUnitId());
}

TEST_F(PlayerListTest, TryingToGetPlayerBodyWithInvalidUnitIdThrowsException) {
    // The list is empty right now
    ASSERT_THROW(list.getPlayerBody(unit_id), PlayerNotFound );
}

TEST_F(PlayerListTest, TryingToGetPlayerMindWithInvalidUnitIdThrowsException) {
    // The list is empty right now
    ASSERT_THROW(list.getPlayerMind(unit_id), PlayerNotFound );
}

TEST_F(PlayerListTest, TryingToAddAnAlreadyExistingPlayerBodyThrowsException) {
    list.addPlayerBody(PlayerBody(blood, position, unit_info));
    ASSERT_THROW(list.addPlayerBody(PlayerBody(blood, position, unit_info)), PlayerAlreadyExists );
}

TEST_F(PlayerListTest, TryingToAddAnAlreadyExistingPlayerMindThrowsException) {
    list.addPlayerBody(PlayerBody(blood, position, unit_info));
    PlayerMindPtr mind = std::make_unique<PlayerMind>(list.getPlayerBody(unit_id));
    list.addPlayerMind(std::move(mind));
    PlayerMindPtr aSecondMind = std::make_unique<PlayerMind>(list.getPlayerBody(unit_id));

    ASSERT_THROW(list.addPlayerMind(std::move(aSecondMind)), PlayerAlreadyExists );
}
