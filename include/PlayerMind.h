#ifndef PLAYER_MIND_H
#define PLAYER_MIND_H

#include <iostream>
#include "PlayerBody.h"

namespace Monarchy {
	class PlayerMind
	{
	protected:
		const PlayerBody& self;
	public:
		PlayerMind(const PlayerBody& self);
		const UnitId getUnitId() const { return self.getUnitId(); }
		bool hasTheSameSelfAs(const PlayerMind& other) const { return self == other.self; }

	};

	bool operator==(const PlayerMind& first, const PlayerMind& second);
}


#endif /* PLAYER_MIND_H */
