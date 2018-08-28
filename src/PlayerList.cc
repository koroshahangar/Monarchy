#include "PlayerList.h"

using namespace Monarchy;

PlayerList::PlayerList() {}

class PlayerAlreadyExists : public std::exception {
  virtual const char* what() const noexcept override {
    return "Player already exists in the list";
  }
};
class PlayerNotFound : public std::exception {
  virtual const char* what() const noexcept override {
    return "Player not found in the list";
  }
};

PlayerBody& PlayerList::addPlayerBody(PlayerBody&& body) {	
	UnitId id = body.getUnitId();
	if (bodies.find(id) == bodies.end()) {
    	bodies.emplace(id, body);
    	return bodies.at(id);

  	}
	else {
		throw PlayerAlreadyExists();
	}
}
PlayerBody& PlayerList::addPlayerBody(PlayerBody& body) {	
	return addPlayerBody(std::move(body));
}
PlayerBody& PlayerList::getPlayerBody(UnitId id) {	
	if(bodies.find(id) == bodies.end()) {
		throw PlayerNotFound();
	}
	return bodies.at(id);
}

PlayerMind& PlayerList::addPlayerMind(PlayerMind&& mind) {	
	UnitId id = mind.getUnitId();
	if (minds.find(id) == minds.end()) {
    	minds.emplace(id, mind);
    	return minds.at(id);

  	}
	else {
		throw PlayerAlreadyExists();
	}
}
PlayerMind& PlayerList::getPlayerMind(UnitId id) {	
	if(minds.find(id) == minds.end()) {
		throw PlayerNotFound();
	}
	return minds.at(id);
}

