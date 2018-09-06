#include "WorldUpdater.h"

using namespace Monarchy;

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
    case MoveType::Walk :
      handlePlayerWalk(dynamic_cast<PlayerWalk*> (move.get()), player);
      break;
    default :
      throw MoveNotRecognized();
  }
}
