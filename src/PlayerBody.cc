#include "PlayerBody.h"



using namespace Monarchy;

std::ostream& Monarchy::operator<<(std::ostream& os, const UnitType& unit_type) {
	if(unit_type == UnitType::Leader)
		return os << "Leader" << std::endl;
	if(unit_type == UnitType::Archer)
		return os << "Archer" << std::endl;
	if(unit_type == UnitType::Spearman)
		return os << "Spearman" << std::endl;
	return os << "InvalidUnitType" << std::endl;
}

std::ostream& Monarchy::operator<<(std::ostream& os, const PlayerBody& agent) {
	os << "Agent: " << std::endl;
	os << "\tblood: " << agent.getBlood() << std::endl;    	
	os << "\tposition: " << agent.getPosition();    	
	os << "\tunit_type: " << agent.getUnitType();    	
	os << "\tunit_id: " << agent.getUnitId() << std::endl;    	
	return os;
}

PlayerBody::PlayerBody(BloodLevel blood, Position pos, UnitType type, UnitId id): 
	blood(blood), position(pos), unit_type(type), unit_id(id) {}