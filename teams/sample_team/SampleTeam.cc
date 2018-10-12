#include "SampleTeam.h"
#include "SampleMind.h"
#include <memory>

using namespace Monarchy;
using namespace SampleCode;

PlayerMindPtr SampleTeam::getMindFor(PlayerBody& body) {
    PlayerMindPtr mind = std::make_unique<SampleMind>(body);
    return mind;
}
