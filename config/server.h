#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

namespace Monarchy {
struct Parameters {
    const BloodLevel INITIAL_BLOOD_LEVEL = 50;
    const Distance REPRODUCE_MAX_DIST = 3;
    const Distance ARROW_MAX_DIST = 5;
    const Distance SPEAR_MAX_DIST = 2;
    const BloodLevel ARROW_DAMAGE = 5;
    const BloodLevel SPEAR_DAMAGE = 10;
};
}

#endif /* SERVER_CONFIG_H */
