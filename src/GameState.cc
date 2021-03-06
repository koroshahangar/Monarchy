#include "GameState.h"

using namespace Monarchy;

GameState::GameState(PlayerBodyList players): players(players) {
    turn_count = 0;
}

int GameState::getTurnCount() const {
    return turn_count;
}

bool GameState::isWithinBounds(Position position) {
    if(position.x < params.MIN_X || position.x > params.MAX_X)
        return false;
    if(position.y < params.MIN_Y || position.y > params.MAX_Y)
        return false;
    return true;
}

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
    os << "(GameState ";
    os << "<players: ";
    for(auto it = state.players.begin(); it != state.players.end(); it++) {
        os << it->second;
    }
    os << "> ";
    os << "<turn_count: " << state.getTurnCount() << ">";
    os << ")";
    return os;
}
