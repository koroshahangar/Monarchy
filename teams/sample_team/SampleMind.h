#ifndef SAMPLE_MIND_H
#define SAMPLE_MIND_H

#include <vector>
#include "PlayerMind.h"

namespace SampleCode {
using namespace Monarchy;

class SampleMind: public PlayerMind {
  public:
    SampleMind(const PlayerBody& self);
    PlayerMovePtr makeAMove(GameState game_state);
    std::vector<Position> allPossibleWalks(GameState& game_state);
    std::vector<UnitId> allPossibleSpearAttacks(GameState& game_state);
    std::vector<UnitId> allPossibleArrowAttacks(GameState& game_state);
};
}

#endif /* SAMPLE_MIND_H */
