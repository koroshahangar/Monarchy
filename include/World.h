#ifndef WORLD_H
#define WORLD_H

#include "Team.h"
#include "GameState.h"
#include "PlayerList.h"
#include <map>
#include <memory>


namespace Monarchy {
  using TeamPtr = std::unique_ptr<Team>;
  using TeamList = std::map<TeamId, TeamPtr>;
  class World {
    private:
      PlayerList player_list;
      GameState game_state = GameState(player_list.getPlayerBodies());
      TeamList team_list;
      Position getPositionForNewLeader();
      PlayerBody&& getLeaderBody(TeamPtr team);
    public:
      World();
      TeamId getNewTeamId();
      UnitId getNewUnitId();
      void addTeam(TeamPtr team);
      TeamPtr& getTeam(TeamId id);

  };
}


#endif /* WORLD_H */
