#include "GameState.h"

using namespace Monarchy;

GameState::GameState(PlayerBodyList players): players(players) {}

const PlayerBody& GameState::getPlayerBody(UnitId unit) {
    if(players.find(unit) == players.end()) {
        throw UnitIdNotValid();
    }
    return players.at(unit);
}

UnitId GameState::getUnitIdOfPlayerAt(const Position position) {
    for(auto iter = players.begin(); iter != players.end(); ++iter) {
        if(iter->second.getPosition() == position)
            return iter->second.getUnitId();
    }
    return 0;
}

std::ostream& Monarchy::operator<<(std::ostream& os, const GameState state) {
    for(auto it = state.players.begin(); it != state.players.end(); it++) {
        os << it->second << std::endl;
    }
    return os;
}
