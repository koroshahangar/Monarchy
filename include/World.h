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
      PlayerBody getNewPlayerBody(UnitType type, TeamPtr& team, BloodLevel blood, Position position);
      PlayerMindPtr getNewPlayerMind(PlayerBody& body, TeamPtr& team);
      PlayerBody& addNewPlayerBody(PlayerBody body);
      PlayerMindPtr& addNewPlayerMind(PlayerMindPtr mind);
      void initLeader(TeamPtr& team);
    public:
      World();
      TeamId getNewTeamId();
      UnitId getNewUnitId();
      void addTeam(TeamPtr team);
      TeamPtr& getTeam(TeamId id);
      void addPlayer(UnitType type, TeamPtr& team, BloodLevel blood, Position position);
  };
}


#endif /* WORLD_H */
