#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <map>
#include "PlayerBody.h"

namespace Monarchy {
  using PlayerBodyList = const std::map<UnitId, PlayerBody>&;
	class GameState
	{
    public:
    PlayerBodyList players;
    GameState(PlayerBodyList players);
	};
  std::ostream& operator<<(std::ostream& os, const GameState& state);
}


#endif /* GAME_STATE_H */
