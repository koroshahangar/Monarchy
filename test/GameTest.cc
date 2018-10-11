#include "Game.h"
#include "gtest/gtest.h"

using namespace Monarchy;

TEST(Game, TeamsCanBeAddedToTheGame) {
    Game game;
    string team_name = "First Team";
    TeamId team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<Team>(team_name, team_id));
    ASSERT_EQ(game.getWorld().getPlayerBodies().size(), 1);
    ASSERT_EQ(game.getWorld().getPlayerMinds().size(), 1);
    team_name = "Second Team";
    team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<Team>(team_name, team_id));
    ASSERT_EQ(game.getWorld().getPlayerBodies().size(), 2);
    ASSERT_EQ(game.getWorld().getPlayerMinds().size(), 2);
}

TEST(Game, ExecutingNextMoveAltersTheGameState) {
    Game game;
    string team_name = "First Team";
    TeamId team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<Team>(team_name, team_id));

    // We know that by default players just move around
    // So we can use position inequality to check if move has been executed
    Position initial_position = game.getWorld().getPlayerBodies().begin()->second.getPosition();
    game.executeNextMove();
    Position final_position = game.getWorld().getPlayerBodies().begin()->second.getPosition();
    ASSERT_NE(initial_position, final_position);
}

TEST(Game, ExecutingNextMoveIncremenetsTurnCount) {
    Game game;
    string team_name = "First Team";
    TeamId team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<Team>(team_name, team_id));
    int initial_turn_count = game.getWorld().getGameState().getTurnCount();
    game.executeNextMove();
    int final_turn_count = game.getWorld().getGameState().getTurnCount();
    ASSERT_EQ(initial_turn_count + 1, final_turn_count);
}
