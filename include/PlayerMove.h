#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H

#include <string>
#include <sstream>
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
    virtual std::string  getRepr()=0; // get a string representation of the move
    virtual ~PlayerMove() {}
};

using PlayerMovePtr = std::unique_ptr<PlayerMove>;

struct PlayerReproduction final: public PlayerMove {
  public:
    const Position spawn_location;
    const UnitType spawn_type;
    PlayerReproduction(const UnitType type, const Position position);
    std::string getRepr() override final {
        std::stringstream repr;
        repr << "Reproduction onto " << spawn_location;
        return repr.str();
    }
};
struct PlayerWalk final: public PlayerMove {
  public:
    const Position destination;
    PlayerWalk(const Position destination);
    std::string getRepr() override final {
        std::stringstream repr;
        repr << "PlayerWalk to " << destination;
        return repr.str();
    }
};
struct SpearAttack final: public PlayerMove {
  public:
    const UnitId target;
    SpearAttack(const UnitId target);
    std::string getRepr() override final {
        std::stringstream repr;
        repr << "SpearAttack at " << target;
        return repr.str();
    }
};
struct ArrowAttack final: public PlayerMove {
  public:
    const UnitId target;
    ArrowAttack(const UnitId target);
    std::string getRepr() override final {
        std::stringstream repr;
        repr << "ArrowAttack at " << target;
        return repr.str();
    }
};


}


#endif /* PLAYER_MOVE_H */
