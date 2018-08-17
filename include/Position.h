#ifndef POSITION_H
#define POSITION_H

#include <iostream>

namespace Monarchy {

	typedef unsigned short Coordinate;

	class Position
	{
	private:
		Coordinate x;
		Coordinate y;
	public:
		Position(Coordinate x = 0, Coordinate y = 0): x(x), y(y) {};
		const Coordinate getX() const { return x; }
		const Coordinate getY() const { return y; }
	};
	std::ostream& operator<<(std::ostream& os, const Position position);
	
}


#endif /* POSITION_H */
