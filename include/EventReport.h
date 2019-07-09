#ifndef EVENT_REPORT_H
#define EVENT_REPORT_H

#include "../config/server.h"
#include "World.h"

namespace Monarchy {
using Report = const std::string;
namespace EventReport {

// This is an environment report used at the beginning of the game to set up the field and env

Report BattleBegins(Monarchy::World& world);
Report InvalidMove(UnitId agent_id);
Report Spawn(const PlayerBody& child, UnitId parent_id);
Report Walk(const Position& new_pos, UnitId agent_id);
Report Attack(UnitId victim_id, BloodLevel victim_blood, UnitId agent_id);
Report Victory(TeamId winner);
Report Tie();
}
}


#endif /* EVENT_REPORT_H */
