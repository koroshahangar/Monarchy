#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H

#include <string>
#include "Position.h"
#include "PlayerBody.h"

namespace Monarchy {
  enum class MoveType { Reproduce, Walk, SpearAttack, ArrowAttack };
  struct PlayerMove {
    public:
    const MoveType type;
    PlayerMove(const MoveType type);

    PlayerMove(const PlayerMove&) = default;
    PlayerMove(PlayerMove&&) = default;
    PlayerMove& operator=(const PlayerMove&) = default;
    PlayerMove& operator=(PlayerMove&&) = default;
    virtual ~PlayerMove() {}
  };
  struct PlayerReproduction: public PlayerMove {
    public:
      const Position spawn_location;
      const UnitType spawn_type;
      PlayerReproduction(const UnitType type, const Position position);
  };
  struct PlayerWalk: public PlayerMove {
    public:
      const Position destination;
      PlayerWalk(const Position destination);
  };
  struct SpearAttack: public PlayerMove {
    public:
      const Position target;
      SpearAttack(const Position target);
  };
  struct ArrowAttack: public PlayerMove {
    public:
      const Position target;
      ArrowAttack(const Position target);
  };


}


#endif /* PLAYER_MOVE_H */
