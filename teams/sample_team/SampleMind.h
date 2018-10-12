#ifndef SAMPLE_MIND_H
#define SAMPLE_MIND_H

#include "PlayerMind.h"

namespace SampleCode {
using namespace Monarchy;

class SampleMind: public PlayerMind {
  public:
    SampleMind(const PlayerBody& self);
    PlayerMovePtr makeAMove(GameState game_state);
};
}

#endif /* SAMPLE_MIND_H */
