#ifndef WORLD_H
#define WORLD_H

#include "Team.h"
#include "GameState.h"
#include "PlayerList.h"
#include <map>
#include <memory>


namespace Monarchy {
using TeamList = std::map<TeamId, TeamPtr>;

class TeamAlreadyExists : public std::exception {
    virtual const char* what() const noexcept override {
        return "Team already exists in the list";
    }
};
class TeamNotFound : public std::exception {
    virtual const char* what() const noexcept override {
        return "Team not found in the list";
    }
};

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
    GameState& getGameState();
    TeamPtr& getTeam(TeamId id);
    TeamList& getTeams();
    UnitId addPlayer(UnitType type, TeamPtr& team, BloodLevel blood, Position position); // returns new player unit id
    std::map<UnitId, PlayerBody>& getPlayerBodies();
    std::map<UnitId, PlayerMindPtr>& getPlayerMinds();
    PlayerBody& getPlayerBody(UnitId id);
    PlayerMindPtr& getPlayerMind(UnitId id);
    void removeUnit(UnitId unit_id);
};
}


#endif /* WORLD_H */
