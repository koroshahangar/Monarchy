#include "PlayerMind.h"

using namespace Monarchy;

PlayerMind::PlayerMind(const PlayerBody& self): self(self) {}

PlayerMovePtr PlayerMind::makeAMove(GameState game_state) {
    Position pos = self.getPosition();
    Position destination(pos.x, pos.y + 1);
    return std::make_unique<PlayerWalk>(destination);
}

bool Monarchy::operator==(const PlayerMind& first, const PlayerMind& second) {
    return first.hasTheSameSelfAs(second);
}

bool Monarchy::operator!=(const PlayerMind& first, const PlayerMind& second) {
    return !(first == second);
}

