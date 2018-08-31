#include "World.h"

using namespace Monarchy;

#define LEADER_INITIAL_BLOOD_LEVEL 20

World::World() {}

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

void World::addTeam(TeamPtr team) {
  TeamId id = team->getId();
	if (team_list.find(id) == team_list.end()) {
    	team_list.emplace(id, std::move(team));
      initLeader(team_list.at(id));
  	}
	else {
		throw TeamAlreadyExists();
	}
}

TeamPtr& World::getTeam(TeamId id) {
  if(team_list.find(id) == team_list.end()) {
		throw TeamNotFound();
	}
	return team_list.at(id);
}

TeamId World::getNewTeamId() {
  static TeamId current_id = 1;
  return current_id++;
}

UnitId World::getNewUnitId() {
  static UnitId current_id = 1;
  return current_id++;
}

Position World::getPositionForNewLeader(){
  // TODO: Change this to to find randomized locations
  static Coordinate num = 0;
  num += 5;
  return Position(num, num);

}

PlayerBody World::getNewPlayerBody(UnitType unit_type, TeamPtr& team, BloodLevel blood, Position position){
  UnitId unit_id = getNewUnitId();
  TeamId team_id = team->getId();
  UnitInfo unit_info {unit_id, unit_type, team_id};
	return PlayerBody(blood, position, unit_info);
}

PlayerMindPtr World::getNewPlayerMind(PlayerBody& body, TeamPtr& team) {
  return team->getMindFor(body);
}

PlayerBody& World::addNewPlayerBody(PlayerBody body) {
  return player_list.addPlayerBody(body);
}

PlayerMindPtr& World::addNewPlayerMind(PlayerMindPtr mind) {
  return player_list.addPlayerMind(std::move(mind));
}

void World::addPlayer(UnitType type, TeamPtr& team, BloodLevel blood, Position position) {
  PlayerBody& body = addNewPlayerBody(getNewPlayerBody(type, team, blood, position));
  addNewPlayerMind(getNewPlayerMind(body, team));
}

void World::initLeader(TeamPtr& team) {
  BloodLevel blood = LEADER_INITIAL_BLOOD_LEVEL;
  UnitType unit_type = UnitType::Leader;
  Position position = getPositionForNewLeader();

  addPlayer(unit_type, team, blood, position);

}
