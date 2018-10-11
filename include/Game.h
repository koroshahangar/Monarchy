#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include "World.h"
#include "WorldUpdater.h"
#include "Team.h"

namespace Monarchy {
class Game {
  private:
    World world;
    WorldUpdater updater {world};
  public:
    Game();
    World& getWorld();
    WorldUpdater& getUpdater();
    void addTeam(TeamPtr team);
    // Fetch next move and update the world accordingly
    void executeNextMove();
    // Game Loop: keep executing the next move forever
    void run();
};
}


#endif /* GAME_H */
