#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H

#include <string>
#include <memory>
#include "Position.h"
#include "PlayerBody.h"

namespace Monarchy {
enum class MoveType { Reproduce, Walk, SpearAttack, ArrowAttack };
struct PlayerMove {
  protected:
    PlayerMove(const MoveType type);
  public:
    const MoveType type;

    PlayerMove(const PlayerMove&) = delete;
    PlayerMove(PlayerMove&&) = delete;
    PlayerMove& operator=(const PlayerMove&) = delete;
    PlayerMove& operator=(PlayerMove&&) = delete;
    virtual ~PlayerMove() {}
};

using PlayerMovePtr = std::unique_ptr<PlayerMove>;

struct PlayerReproduction final: public PlayerMove {
  public:
    const Position spawn_location;
    const UnitType spawn_type;
    PlayerReproduction(const UnitType type, const Position position);
};
struct PlayerWalk final: public PlayerMove {
  public:
    const Position destination;
    PlayerWalk(const Position destination);
};
struct SpearAttack final: public PlayerMove {
  public:
    const UnitId target;
    SpearAttack(const UnitId target);
};
struct ArrowAttack final: public PlayerMove {
  public:
    const UnitId target;
    ArrowAttack(const UnitId target);
};


}


#endif /* PLAYER_MOVE_H */
