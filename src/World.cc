#include "World.h"

using namespace Monarchy;

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
