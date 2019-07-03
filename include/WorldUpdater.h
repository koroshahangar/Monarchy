#ifndef WORLD_UPDATER_H
#define WORLD_UPDATER_H

#include "PlayerMind.h"
#include "PlayerMove.h"
#include "World.h"
#include <string>

namespace Monarchy {

class MoveNotRecognized : public std::exception {
    virtual const char* what() const noexcept override {
        return "PlayerMove type cannot be recognized";
    }
};

class MoveNotValid : public std::exception {
    virtual const char* what() const noexcept override {
        return "PlayerMove is not valid";
    }
};

class WorldUpdater {
  private:
    World& world;
    GameState& game_state = world.getGameState();
    bool isPlayerReproductionValid(PlayerReproduction* move, UnitId player);
    void handlePlayerReproduction(PlayerReproduction* move, UnitId player);
    bool isPlayerWalkValid(PlayerWalk* move, UnitId player);
    void handlePlayerWalk(PlayerWalk* move, UnitId player);
    bool isArrowAttackValid(ArrowAttack* move, UnitId player);
    void handleArrowAttack(ArrowAttack* move, UnitId player);
    bool isSpearAttackValid(SpearAttack* move, UnitId player);
    void handleSpearAttack(SpearAttack* move, UnitId player);
    bool removeUnitIfDead(UnitId unit_id);
  public:
    bool game_has_ended;
    WorldUpdater(World& world): world(world) {
        game_has_ended = false;
    }
    void handleMove(PlayerMovePtr& move, UnitId player);

};

}


#endif /* WORLD_UPDATER_H */
