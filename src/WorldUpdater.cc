#include "WorldUpdater.h"

using namespace Monarchy;

void WorldUpdater::removeUnitIfDead(UnitId unit_id) {
    if(world.getGameState().getPlayerBody(unit_id).getBlood() < 1) {
        if(world.getPlayerBody(unit_id).getUnitType() == UnitType::Leader)
            this->game_has_ended = true;
        world.removeUnit(unit_id);
    }
}

bool WorldUpdater::isPlayerReproductionValid(PlayerReproduction* move, UnitId player) {
    // Check if player is a leader
    const PlayerBody& agent = game_state.getPlayerBody(player);
    if(agent.getUnitType() != UnitType::Leader)
        return false;
    // Check if the position is within bounds
    if(game_state.isWithinBounds(move->spawn_location) == false)
        return false;
    // Check if the position is empty
    if(game_state.getUnitIdOfPlayerAt(move->spawn_location) != 0)
        return false;
    if(agent.getPosition().getBlockDistanceFrom(move->spawn_location) > game_state.params.REPRODUCE_MAX_DIST)
        return false;
    if(move->spawn_type == UnitType::Leader)
        return false;
    return true;
}
void WorldUpdater::handlePlayerReproduction(PlayerReproduction* move, UnitId player) {
    if(!isPlayerReproductionValid(move, player))
        throw MoveNotValid();
    const PlayerBody& leader = game_state.getPlayerBody(player);
    BloodLevel initial_blood_level = game_state.params.INITIAL_BLOOD_LEVEL;
    world.addPlayer(move->spawn_type, world.getTeam(leader.getTeamId()), initial_blood_level, move->spawn_location);
}
bool WorldUpdater::isPlayerWalkValid(PlayerWalk* move, UnitId player) {
    const PlayerBody& agent = game_state.getPlayerBody(player);
    // Check if the position is within bounds
    if(game_state.isWithinBounds(move->destination) == false)
        return false;
    // Check if the position is empty
    if(game_state.getUnitIdOfPlayerAt(move->destination) != 0)
        return false;
    if(agent.getPosition().getBlockDistanceFrom(move->destination) > 1)
        return false;
    return true;
}
void WorldUpdater::handlePlayerWalk(PlayerWalk* move, UnitId player) {
    if(!isPlayerWalkValid(move, player))
        throw MoveNotValid();
    world.getPlayerBody(player).position = move->destination;
}

bool WorldUpdater::isArrowAttackValid(ArrowAttack* move, UnitId player) {
    const PlayerBody& agent = game_state.getPlayerBody(player);
    const PlayerBody& target = game_state.getPlayerBody(move->target);

    if(agent.getUnitType() != UnitType::Archer)
        return false;

    if(agent.getPosition().getBlockDistanceFrom(target.getPosition()) > game_state.params.ARROW_MAX_DIST)
        return false;
    return true;

}
void WorldUpdater::handleArrowAttack(ArrowAttack* move, UnitId player) {
    if(!isArrowAttackValid(move, player))
        throw MoveNotValid();
    world.getPlayerBody(move->target).blood -= game_state.params.ARROW_DAMAGE;
    removeUnitIfDead(move->target);
}

bool WorldUpdater::isSpearAttackValid(SpearAttack* move, UnitId player) {
    const PlayerBody& agent = game_state.getPlayerBody(player);
    const PlayerBody& target = game_state.getPlayerBody(move->target);
    if(agent.getUnitType() != UnitType::Spearman)
        return false;
    if(agent.getPosition().getBlockDistanceFrom(target.getPosition()) > game_state.params.SPEAR_MAX_DIST)
        return false;
    return true;
}

void WorldUpdater::handleSpearAttack(SpearAttack* move, UnitId player) {
    if(!isSpearAttackValid(move, player))
        throw MoveNotValid();
    world.getPlayerBody(move->target).blood -= game_state.params.SPEAR_DAMAGE;
    removeUnitIfDead(move->target);
}

void WorldUpdater::handleMove(PlayerMovePtr& move, UnitId player) {
    switch(move->type) {
    case MoveType::Reproduce :
        handlePlayerReproduction(dynamic_cast<PlayerReproduction*> (move.get()), player);
        break;
    case MoveType::Walk :
        handlePlayerWalk(dynamic_cast<PlayerWalk*> (move.get()), player);
        break;
    case MoveType::ArrowAttack :
        handleArrowAttack(dynamic_cast<ArrowAttack*> (move.get()), player);
        break;
    case MoveType::SpearAttack :
        handleSpearAttack(dynamic_cast<SpearAttack*> (move.get()), player);
        break;
    default :
        throw MoveNotRecognized();
    }
}
