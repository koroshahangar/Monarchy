#ifndef WORLD_UPDATER_H
#define WORLD_UPDATER_H

#include "PlayerMind.h"
#include "PlayerMove.h"
#include "World.h"
#include <string>

namespace Monarchy {
class WorldUpdater {
  private:
    World& world;
    GameState& game_state = world.getGameState();
    bool isPlayerReproductionValid(PlayerReproduction* move, UnitId player);
    void handlePlayerReproduction(PlayerReproduction* move, UnitId player);
    bool isPlayerWalkValid(PlayerWalk* move, UnitId player);
    void handlePlayerWalk(PlayerWalk* move, UnitId player);
  public:
    WorldUpdater(World& world): world(world) {}
    void handleMove(PlayerMovePtr& move, UnitId player);

};

}


#endif /* WORLD_UPDATER_H */
