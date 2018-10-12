#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <map>
#include "PlayerBody.h"
#include "../config/server.h"

namespace Monarchy {
using PlayerBodyList = const std::map<UnitId, PlayerBody>&;

class UnitIdNotValid : public std::exception {
    virtual const char* what() const noexcept override {
        return "Given UnitId does not correspond to any alive agent";
    }
};

// Forward declaration in order to make game a friend of class GameState
class Game;

class GameState {
    friend class Game;
  private:
    int turn_count;
  public:
    PlayerBodyList players;
    int getTurnCount() const;
    GameState(PlayerBodyList players);
    const PlayerBody& getPlayerBody(UnitId unit);
    UnitId getUnitIdOfPlayerAt(const Position position);
    bool isWithinBounds(Position position);

    struct Parameters params;
};
std::ostream& operator<<(std::ostream& os, const GameState state);
}


#endif /* GAME_STATE_H */
