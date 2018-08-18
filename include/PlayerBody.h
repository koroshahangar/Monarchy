#ifndef PLAYER_BODY_H
#define PLAYER_BODY_H

#include <iostream>
#include "Position.h"

namespace Monarchy {

	typedef unsigned short BloodLevel;
	typedef unsigned short UnitId;
	typedef unsigned short TeamId;
	enum class UnitType { Leader, Archer, Spearman };
	std::ostream& operator<<(std::ostream& os, const UnitType& unit_type);

	class PlayerBody
	{
	private:
		BloodLevel blood;
		Position position;	
		UnitType unit_type;
		UnitId unit_id;
		TeamId team_id;
	public:
		PlayerBody(BloodLevel blood, Position position, UnitType type, UnitId id);
		const BloodLevel getBlood() const { return blood; }
		const Position getPosition() const { return position; }
		const UnitType getUnitType() const { return unit_type; }
		const UnitId getUnitId() const { return unit_id; }
		const UnitId getTeamId() const { return team_id; }

	};
	std::ostream& operator<<(std::ostream& os, const PlayerBody& agent);


}


#endif /* PLAYER_BODY_H */
