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
