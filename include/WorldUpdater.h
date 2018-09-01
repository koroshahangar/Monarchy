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
    WorldUpdater(World& world): world(world) {}
    public:
    bool isMoveValid(PlayerMovePtr& move);
    void handleMove(PlayerMovePtr& move);
  };

}


#endif /* WORLD_UPDATER_H */
