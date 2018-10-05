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

class GameState {
  public:
    PlayerBodyList players;
    GameState(PlayerBodyList players);
    const PlayerBody& getPlayerBody(UnitId unit);
    UnitId getUnitIdOfPlayerAt(const Position position);

    struct Parameters params;
};
}


#endif /* GAME_STATE_H */
