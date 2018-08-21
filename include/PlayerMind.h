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
	};
}


#endif /* PLAYER_MIND_H */
