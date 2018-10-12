#include "PlayerBody.h"



using namespace Monarchy;

std::ostream& Monarchy::operator<<(std::ostream& os, const UnitType& unit_type) {
    if(unit_type == UnitType::Leader)
        return os << "Leader";
    if(unit_type == UnitType::Archer)
        return os << "Archer";
    if(unit_type == UnitType::Spearman)
        return os << "Spearman";
    return os << "InvalidUnitType";
}

std::ostream& Monarchy::operator<<(std::ostream& os, const PlayerBody& agent) {
    os << "(Player ";
    os << "<untit_id: " << agent.getUnitId() << "> ";
    os << "<team_id: " << agent.getTeamId() << ">";
    os << "<unit_type: " << agent.getUnitType() << "> ";
    os << "<blood: " << agent.getBlood() << "> ";
    os << "<position: " << agent.getPosition() << "> ";
    os << ")";
    return os;
}

PlayerBody::PlayerBody(BloodLevel blood, Position pos, UnitInfo unit_info):
    blood(blood), position(pos), unit_info(unit_info) {}

bool Monarchy::operator ==(const PlayerBody& first, const PlayerBody& second) {
    return first.getUnitId() == second.getUnitId();
}
bool Monarchy::operator !=(const PlayerBody& first, const PlayerBody& second) {
    return !(first == second);
}
