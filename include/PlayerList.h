#ifndef PLAYER_LIST_H
#define PLAYER_LIST_H

#include <map>
#include <iostream>
#include "PlayerBody.h"
#include "PlayerMind.h"

namespace Monarchy {
class PlayerList {
  private:
    friend class World;
    std::map<UnitId, PlayerMindPtr> minds;
    std::map<UnitId, PlayerBody> bodies;
  public:
    PlayerList();
    PlayerBody& addPlayerBody(PlayerBody&& body);
    PlayerBody& addPlayerBody(PlayerBody& body);
    PlayerBody& getPlayerBody(UnitId id);

    PlayerMindPtr& addPlayerMind(PlayerMindPtr mind);
    PlayerMindPtr& getPlayerMind(UnitId id);

    const std::map<UnitId, PlayerBody>& getPlayerBodies() const;
};
}


#endif /* PLAYER_LIST_H */
