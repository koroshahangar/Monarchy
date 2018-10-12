#ifndef SAMPLE_TEAM_H
#define SAMPLE_TEAM_H

#include "PlayerMind.h"
#include "Team.h"
#include <string>

namespace SampleCode {

using namespace Monarchy;

class SampleTeam: public Team {
  public:
    SampleTeam(std::string name, TeamId id): Team(name, id) {}
    PlayerMindPtr getMindFor(PlayerBody& body);
};
}
#endif /* SAMPLE_TEAM_H */
