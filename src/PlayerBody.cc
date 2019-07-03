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
    // (Player unit_id team_id unit_type blood [position_x position_y])
    os << "(Player ";
    os << agent.getUnitId() << " ";
    os << agent.getTeamId() << " ";
    os << agent.getUnitType() << " ";
    os << agent.getBlood() << " ";
    os << agent.getPosition() << ")";
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
