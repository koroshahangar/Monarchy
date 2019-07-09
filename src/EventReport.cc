#include "EventReport.h"
#include <sstream>

using namespace Monarchy;

Report EventReport::BattleBegins(Monarchy::World& world ) {
    Monarchy::Parameters& params = world.getGameState().params;
    TeamList& teams = world.getTeams();
    std::map<UnitId, PlayerBody>& agents = world.getPlayerBodies();
    std::ostringstream report("");

    report  << "Env "
            << "{MaxCount " << params.MAX_TURN_COUNT << "} ";

    report << "{MaxBlood "
           << params.INITIAL_BLOOD_LEVEL << "} ";

    report << "{Field "
           << params.MIN_X << " " << params.MAX_X << " "
           << params.MIN_Y << " " << params.MAX_Y << " "<< "} ";

    report << "{Teams ";
    for(auto const& team_tuple: teams) {
        report << *team_tuple.second;
    }
    report << "} ";

    report << "{Agents ";
    for(auto const& agent_tuple: agents) {
        report << agent_tuple.second;
    }
    report<< "} ";

    return report.str();
}

Report EventReport::InvalidMove(UnitId agent_id) {
    std::ostringstream report("");
    report << "Invalid " << agent_id;
    return report.str();
}
Report EventReport::Spawn(const PlayerBody& child, UnitId parent_id) {
    std::ostringstream report("");
    report << "Spawn {" << child << "} " << parent_id;
    return report.str();
}
Report EventReport::Walk(const Position& new_pos, UnitId agent_id) {
    std::ostringstream report("");
    report << "Walk " << new_pos << " " << agent_id;
    return report.str();
}
Report EventReport::Attack(UnitId victim_id, BloodLevel victim_blood, UnitId attacker_id) {
    std::ostringstream report("");
    report << "Attack " << victim_id << " " << victim_blood << " " << attacker_id;
    return report.str();
}
Report EventReport::Victory(TeamId winner) {
    std::ostringstream report("");
    report << "Victory " << winner;
    return report.str();
}
Report EventReport::Tie() {
    return "Tie";
}
