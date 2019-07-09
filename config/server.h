#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include "PlayerBody.h"

namespace Monarchy {
struct Parameters {
    const BloodLevel INITIAL_BLOOD_LEVEL = 50;
    const Distance REPRODUCE_MAX_DIST = 3;
    const Distance ARROW_MAX_DIST = 5;
    const Distance SPEAR_MAX_DIST = 2;
    const BloodLevel ARROW_DAMAGE = 5;
    const BloodLevel SPEAR_DAMAGE = 10;
    const Coordinate MAX_X = 50;
    const Coordinate MAX_Y = 50;
    const Coordinate MIN_X = 0;
    const Coordinate MIN_Y = 0;
    const int MAX_TURN_COUNT = 1500;
};
}

#endif /* SERVER_CONFIG_H */
