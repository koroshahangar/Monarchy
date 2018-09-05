#ifndef POSITION_H
#define POSITION_H

#include <iostream>

namespace Monarchy {

	typedef unsigned short Coordinate;
  typedef unsigned short Distance;

	class Position
	{
	public:
		Coordinate x;
		Coordinate y;

    Distance getBlockDistanceFrom(const Position& other) const;

		Position(Coordinate x = 0, Coordinate y = 0): x(x), y(y) {};

	};
	std::ostream& operator<<(std::ostream& os, const Position position);
	bool operator ==(const Position& first, const Position& second);
	bool operator !=(const Position& first, const Position& second);

}


#endif /* POSITION_H */
