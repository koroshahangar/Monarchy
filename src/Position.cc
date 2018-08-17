#include "Position.h"

using namespace Monarchy;

std::ostream& operator<<(std::ostream& os, const Position position) {
	return os << "Position: (" 
		<< position.getX() << ", " 
		<< position.getY() << ")" 
		<< std::endl ;
}