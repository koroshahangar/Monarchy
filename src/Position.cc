#include "Position.h"

using namespace Monarchy;

std::ostream& Monarchy::operator<<(std::ostream& os, const Position position) {
	return os << "Position: (" 
		<< position.x << ", " 
		<< position.y << ")" 
		<< std::endl ;
}