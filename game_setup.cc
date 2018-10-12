#include "Game.h"
#include "SampleTeam.h"
using namespace Monarchy;

int main() {
    Game game;
    string team_name = "First Team";
    TeamId team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<SampleCode::SampleTeam>(team_name, team_id));
    team_name = "Second Team";
    team_id = game.getWorld().getNewTeamId();
    game.addTeam(std::make_unique<SampleCode::SampleTeam>(team_name, team_id));
    game.run();
    return 0;
}
