#ifndef WORLD_H
#define WORLD_H

#include "Team.h"
#include "GameState.h"
#include "PlayerList.h"
#include <map>
#include <memory>


namespace Monarchy {
  using TeamList = std::map<TeamId, std::unique_ptr<Team>>;
  class World {
    private:
      PlayerList player_list;
      GameState game_state = GameState(player_list.getPlayerBodies());
      TeamList team_list;
    public:
      World();
  };
}


#endif /* WORLD_H */
