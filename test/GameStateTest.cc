#include "GameState.h"
#include "PlayerList.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(GameState, GetUnitIdofPlayerAtReturnsZeroForEmptyPositions) {
    PlayerList list;
    for(int x = 5, y = 5; x < 11; ) {
        // Player Body
        BloodLevel blood = 15;
        Position position(x, y);
        UnitType unit_type = UnitType::Leader;
        UnitId unit_id = x;
        TeamId team_id = 1;
        UnitInfo unit_info {unit_id, unit_type, team_id};
        PlayerBody body(blood, position, unit_info);
        list.addPlayerBody(body);
        x++;
        y++;
    }
    GameState game_state(list.getPlayerBodies());
    UnitId ui;
    ui = game_state.getUnitIdOfPlayerAt(Position(2,2));
    ASSERT_EQ(ui, 0);
    ui = game_state.getUnitIdOfPlayerAt(Position(11,11));
    ASSERT_EQ(ui, 0);
}
TEST(GameState, GetUnitIdofPlayerAtReturnsTheRightUnitId) {
    PlayerList list;
    for(int x = 5, y = 5; x < 11; ) {
        // Player Body
        BloodLevel blood = 15;
        Position position(x, y);
        UnitType unit_type = UnitType::Leader;
        UnitId unit_id = x;
        TeamId team_id = 1;
        UnitInfo unit_info {unit_id, unit_type, team_id};
        PlayerBody body(blood, position, unit_info);
        list.addPlayerBody(body);
        x++;
        y++;
    }
    GameState game_state(list.getPlayerBodies());
    UnitId ui;
    ui = game_state.getUnitIdOfPlayerAt(Position(5,5));
    ASSERT_EQ(ui, 5);
    ui = game_state.getUnitIdOfPlayerAt(Position(6,6));
    ASSERT_EQ(ui, 6);
    ui = game_state.getUnitIdOfPlayerAt(Position(7,7));
    ASSERT_EQ(ui, 7);
    ui = game_state.getUnitIdOfPlayerAt(Position(8,8));
    ASSERT_EQ(ui, 8);
    ui = game_state.getUnitIdOfPlayerAt(Position(9,9));
    ASSERT_EQ(ui, 9);
    ui = game_state.getUnitIdOfPlayerAt(Position(10,10));
    ASSERT_EQ(ui, 10);
}
