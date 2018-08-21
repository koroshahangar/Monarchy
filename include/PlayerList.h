#ifndef PLAYER_LIST_H
#define PLAYER_LIST_H

#include <map>
#include "PlayerBody.h"
#include "PlayerMind.h"

namespace Monarchy {
	class PlayerList
	{
	private:
		std::map<UnitId, PlayerBody> minds;
		std::map<UnitId, PlayerMind> bodies;
	public:
		PlayerList();		
	};
}


#endif /* PLAYER_LIST_H */
