#ifndef PLAYER_MIND_H
#define PLAYER_MIND_H

#include <iostream>
#include "PlayerBody.h"

namespace Monarchy {
	class PlayerMind
	{
	protected:
		const UnitId self;
	public:
		PlayerMind(UnitId self);
	};
}


#endif /* PLAYER_MIND_H */
