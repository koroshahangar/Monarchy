#include "Team.h"
#include <memory>

using namespace Monarchy;

PlayerMindPtr Team::getMindFor(PlayerBody& body) {
    PlayerMindPtr mind = std::make_unique<PlayerMind>(body);
    return mind;
}

std::ostream& Monarchy::operator<<(std::ostream& os, const Team& team) {
    // (Team team_id team_name)
    os << "(Team " << team.getId() << " " << team.getName() << ")";
    return os;
}
