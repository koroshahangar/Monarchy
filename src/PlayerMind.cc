#include "PlayerMind.h"

using namespace Monarchy;

PlayerMind::PlayerMind(const PlayerBody& self): self(self) {}

bool Monarchy::operator==(const PlayerMind& first, const PlayerMind& second) {
	return first.hasTheSameSelfAs(second);
}
