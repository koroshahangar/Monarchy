#include "SampleMind.h"
using namespace SampleCode;

SampleMind::SampleMind(const PlayerBody& self): PlayerMind(self) {

}

PlayerMovePtr SampleMind::makeAMove(GameState game_state) {
  Position pos = self.getPosition();
  Position destination(pos.x, pos.y + 1);
  if(self.getUnitType() == UnitType::Leader) {
      std::cout << "Reproducing" << std::endl;
      return std::make_unique<PlayerReproduction>(UnitType::Archer, destination);
  }
  std::cout << "Moving" << std::endl;
  return std::make_unique<PlayerWalk>(destination);
}
