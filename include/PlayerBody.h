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

	struct UnitInfo
	{
		UnitId id;		
		UnitType type;
		TeamId team_id;
	};

	class PlayerBody
	{
	private:
		BloodLevel blood;
		Position position;	
		UnitInfo unit_info;
	public:
		PlayerBody(BloodLevel blood, Position position, UnitInfo unit_info);
		const BloodLevel getBlood() const { return blood; }
		const Position getPosition() const { return position; }
		const UnitType getUnitType() const { return unit_info.type; }
		const UnitId getUnitId() const { return unit_info.id; }
		const UnitId getTeamId() const { return unit_info.team_id; }

	};
	std::ostream& operator<<(std::ostream& os, const PlayerBody& agent);


}


#endif /* PLAYER_BODY_H */
