#include "WorldUpdater.h"

using namespace Monarchy;

#define INITIAL_BLOOD_LEVEL 50

class MoveNotRecognized : public std::exception {
    virtual const char* what() const noexcept override {
        return "PlayerMove is not recognized";
    }
};

class MoveNotValid : public std::exception {
    virtual const char* what() const noexcept override {
        return "PlayerMove is not valid";
    }
};

bool WorldUpdater::isPlayerReproductionValid(PlayerReproduction* move, UnitId player) {
    // Check if player is a leader
    const PlayerBody& agent = game_state.getPlayerBody(player);
    if(agent.getUnitType() != UnitType::Leader)
        return false;
    // Check if the position is empty
    if(game_state.getUnitIdOfPlayerAt(move->spawn_location) != 0)
        return false;
    return true;
}
void WorldUpdater::handlePlayerReproduction(PlayerReproduction* move, UnitId player) {
    if(!isPlayerReproductionValid(move, player))
        throw MoveNotValid();
    const PlayerBody& leader = game_state.getPlayerBody(player);
    BloodLevel initial_blood_level = INITIAL_BLOOD_LEVEL;
    world.addPlayer(move->spawn_type, world.getTeam(leader.getTeamId()), initial_blood_level, move->spawn_location);
}
bool WorldUpdater::isPlayerWalkValid(PlayerWalk* move, UnitId player) {
    const PlayerBody& agent = game_state.getPlayerBody(player);
    if(agent.getPosition().getBlockDistanceFrom(move->destination) > 1)
        return false;
    return true;

}

void WorldUpdater::handlePlayerWalk(PlayerWalk* move, UnitId player) {
    if(!isPlayerWalkValid(move, player))
        throw MoveNotValid();
    world.getPlayerBody(player).position = move->destination;
}

void WorldUpdater::handleMove(PlayerMovePtr& move, UnitId player) {
    switch(move->type) {
    case MoveType::Reproduce :
        handlePlayerReproduction(dynamic_cast<PlayerReproduction*> (move.get()), player);
        break;
    case MoveType::Walk :
        handlePlayerWalk(dynamic_cast<PlayerWalk*> (move.get()), player);
        break;
    default :
        throw MoveNotRecognized();
    }
}
