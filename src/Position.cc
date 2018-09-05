#include "Position.h"

using namespace Monarchy;


std::ostream& Monarchy::operator<<(std::ostream& os, const Position position) {
	return os << "Position: ("
		<< position.x << ", "
		<< position.y << ")"
		<< std::endl ;
}

bool Monarchy::operator ==(const Position& first, const Position& second) {
	return first.x == second.x && first.y == second.y;
}

bool Monarchy::operator !=(const Position& first, const Position& second) {
	return !(first == second);
}

Distance Position::getBlockDistanceFrom(const Position& other) const {
  return std::abs(x - other.x) + std::abs(y - other.y);
}
