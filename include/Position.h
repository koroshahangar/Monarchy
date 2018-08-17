#ifndef POSITION_H
#define POSITION_H

#include <iostream>

namespace Monarchy {

	typedef unsigned short Coordinate;

	class Position
	{		
	public:
		Coordinate x;
		Coordinate y;

		Position(Coordinate x = 0, Coordinate y = 0): x(x), y(y) {};		
	};
	std::ostream& operator<<(std::ostream& os, const Position position);
	
}


#endif /* POSITION_H */
