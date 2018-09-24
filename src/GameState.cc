#include "GameState.h"

using namespace Monarchy;

class UnitIdNotValid : public std::exception {
    virtual const char* what() const noexcept override {
        return "Given UnitId does not correspond to any alive agent";
    }
};


GameState::GameState(PlayerBodyList players): players(players) {}

const PlayerBody& GameState::getPlayerBody(UnitId unit) {
    if(players.find(unit) == players.end()) {
        throw UnitIdNotValid();
    }
    return players.at(unit);
}

