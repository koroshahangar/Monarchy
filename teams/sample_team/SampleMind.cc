#include "SampleMind.h"
#include <time.h>
using namespace SampleCode;

SampleMind::SampleMind(const PlayerBody& self): PlayerMind(self) {

}

PlayerMovePtr SampleMind::makeAMove(GameState game_state) {
  srand (time(NULL));
  if(self.getUnitType() == UnitType::Leader) { // Reproduce if you can
    auto walks = allPossibleWalks(game_state);
    if(walks.size() > 0) {
      int ind = std::rand() % walks.size();
      Position rand_pos = walks.at(ind);
      return std::make_unique<PlayerReproduction>(UnitType::Archer, rand_pos);
    }
  }
  if(self.getUnitType() == UnitType::Spearman) { // Attack if you can
    auto targets = allPossibleSpearAttacks(game_state);
    if(targets.size() > 0) {
      int ind = std::rand() % targets.size();
      UnitId rand_target = targets.at(ind);
      return std::make_unique<SpearAttack>(rand_target);
    }
  }
  if(self.getUnitType() == UnitType::Archer) { // Attack if you can
    auto targets = allPossibleArrowAttacks(game_state);
    if(targets.size() > 0) {
      int ind = std::rand() % targets.size();
      UnitId rand_target = targets.at(ind);
      return std::make_unique<ArrowAttack>(rand_target);
    }
  }

  // Worst-Case Scenario just walk somewhere else
  auto walks = allPossibleWalks(game_state);
  if(walks.size() > 0) {
    int ind = std::rand() % walks.size();
    Position rand_pos = walks.at(ind);
    return std::make_unique<PlayerWalk>(rand_pos);
  }
  return std::make_unique<PlayerWalk>(Position(0,0));
}

std::vector<Position> SampleMind::allPossibleWalks(GameState& game_state){
  std::vector<Position> moves;
  // Get all possible locations to walk to
  for(int x = self.getPosition().x - 1; x < self.getPosition().x + 2; x++) {
    for(int y = self.getPosition().y - 1; y < self.getPosition().y + 2; y++) {
      Position candid_pos(x,y);
      if(!game_state.isWithinBounds(candid_pos)) // ignore if out of bound
        continue;
      if(game_state.getUnitIdOfPlayerAt(candid_pos) != 0) // ignore if occupied
        continue;
      if(candid_pos.getBlockDistanceFrom(self.getPosition()) > 1) // no diagonal
        continue;
      moves.push_back(candid_pos);
    }
  }
  return moves;
}

std::vector<UnitId> SampleMind::allPossibleSpearAttacks(GameState& game_state) {
  std::vector<UnitId> targets;
  Distance smd = game_state.params.SPEAR_MAX_DIST;
  // Get all possible locations to walk to
  for(int x = self.getPosition().x - smd; x < self.getPosition().x + smd + 1; x++) {
    for(int y = self.getPosition().y - smd; y < self.getPosition().y + smd + 1; y++) {
      Position candid_pos(x,y);
      if(!game_state.isWithinBounds(candid_pos)) // ignore if out of bound
        continue;
      if(game_state.getUnitIdOfPlayerAt(candid_pos) == 0) // ignore if occupied
        continue;
      if(candid_pos.getBlockDistanceFrom(self.getPosition()) > smd) // no diagonal
        continue;
      UnitId player_id = game_state.getUnitIdOfPlayerAt(candid_pos);
      if(game_state.getPlayerBody(player_id).getTeamId() == self.getTeamId())
        continue; // ignore if a team mate is there
      targets.push_back(player_id);
    }
  }
  return targets;
}

std::vector<UnitId> SampleMind::allPossibleArrowAttacks(GameState& game_state) {
  std::vector<UnitId> targets;
  Distance amd = game_state.params.ARROW_MAX_DIST;
  // Get all possible locations to walk to
  for(int x = self.getPosition().x - amd; x < self.getPosition().x + amd + 1; x++) {
    for(int y = self.getPosition().y - amd; y < self.getPosition().y + amd + 1; y++) {
      Position candid_pos(x,y);
      if(!game_state.isWithinBounds(candid_pos)) // ignore if out of bound
        continue;
      if(game_state.getUnitIdOfPlayerAt(candid_pos) == 0) // ignore if occupied
        continue;
      if(candid_pos.getBlockDistanceFrom(self.getPosition()) > amd) // no diagonal
        continue;
      UnitId player_id = game_state.getUnitIdOfPlayerAt(candid_pos);
      if(game_state.getPlayerBody(player_id).getTeamId() == self.getTeamId())
        continue; // ignore if a team mate is there
      targets.push_back(player_id);
    }
  }
  return targets;
}
