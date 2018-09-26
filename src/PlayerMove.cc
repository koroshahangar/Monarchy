#include "PlayerMove.h"

using namespace Monarchy;

PlayerMove::PlayerMove(const MoveType type): type(type) {}

PlayerReproduction::PlayerReproduction(const UnitType type, const Position position):
    PlayerMove(MoveType::Reproduce),
    spawn_location(position), spawn_type(type) {}

PlayerWalk::PlayerWalk(const Position destination):
    PlayerMove(MoveType::Walk),
    destination(destination) {}

SpearAttack::SpearAttack(const UnitId target):
    PlayerMove(MoveType::SpearAttack),
    target(target) {}

ArrowAttack::ArrowAttack(const UnitId target):
    PlayerMove(MoveType::ArrowAttack),
    target(target) {}

