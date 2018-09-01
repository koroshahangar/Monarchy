#ifndef PLAYER_MIND_H
#define PLAYER_MIND_H

#include <iostream>
#include <memory>
#include "PlayerBody.h"
#include "PlayerMove.h"
#include "GameState.h"

namespace Monarchy {

	class PlayerMind
	{
	protected:
		const PlayerBody& self;
	public:
		PlayerMind(const PlayerBody& self);
		const UnitId getUnitId() const { return self.getUnitId(); }
		bool hasTheSameSelfAs(const PlayerMind& other) const { return self == other.self; }
    virtual PlayerMovePtr makeAMove(GameState game_state);
    PlayerMind(const PlayerMind&) = default;
    PlayerMind(PlayerMind&&) = default;
    PlayerMind& operator=(const PlayerMind&) = default;
    PlayerMind& operator=(PlayerMind&&) = default;
    virtual ~PlayerMind() {}

	};

	bool operator==(const PlayerMind& first, const PlayerMind& second);
	bool operator!=(const PlayerMind& first, const PlayerMind& second);

  using PlayerMindPtr = std::unique_ptr<PlayerMind>;
}


#endif /* PLAYER_MIND_H */
