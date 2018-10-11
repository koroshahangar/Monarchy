#ifndef TEAM_H
#define TEAM_H

#include "PlayerMind.h"
#include <string>

namespace Monarchy {
using string = std::string;
class Team {
  private:
    string name;
    TeamId id;
  public:
    Team(string name, TeamId id): name(name), id(id) {}
    const string getName() const {
        return name;
    }
    const TeamId getId() const {
        return id;
    }
    virtual PlayerMindPtr getMindFor(PlayerBody& body);
    virtual ~Team() {}
};
using TeamPtr = std::unique_ptr<Team>;
}


#endif /* TEAM_H */
