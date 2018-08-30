#include "Team.h"

using namespace Monarchy;

PlayerMind Team::getMindFor(PlayerBody& body) {
  PlayerMind mind(body);
  return mind;
}
