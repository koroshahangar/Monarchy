#include "Team.h"
#include <memory>

using namespace Monarchy;

PlayerMindPtr Team::getMindFor(PlayerBody& body) {
    PlayerMindPtr mind = std::make_unique<PlayerMind>(body);
    return mind;
}
