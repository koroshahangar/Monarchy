#include "PlayerMind.h"
#include "gtest/gtest.h"

using namespace Monarchy;

class PlayerMindTest : public ::testing::Test {
  protected:
    PlayerMindTest():
        body(blood, position, UnitInfo {unit_id, unit_type, team_id}) {

    }

    PlayerBody body;
    BloodLevel blood {15};
    Position position {10, 15};
    UnitType unit_type = UnitType::Leader;
    UnitId unit_id = 5;
    TeamId team_id = 1;
};


TEST_F(PlayerMindTest, ConstructorWorksInASimpleCase) {
    PlayerMind mind(body);

    ASSERT_EQ(mind.getUnitId(), body.getUnitId());
}

TEST_F(PlayerMindTest, EqaulityOperatorOnlyChecksBodyEquality) {

    PlayerMind mind1(body);
    PlayerMind mind2(body);

    ASSERT_EQ(mind1, mind2);
}

TEST_F(PlayerMindTest, NotEqualOperatorOnlyChecksBodyEquality) {
    UnitId another_unit_id = unit_id + 1;
    PlayerBody another_body(blood, position, UnitInfo{another_unit_id, unit_type, team_id});

    PlayerMind mind1(body);
    PlayerMind mind2(another_body);
    PlayerMind mind3(body);

    ASSERT_NE(mind1, mind2);
    ASSERT_NE(mind3, mind2);
    ASSERT_EQ(mind3, mind1);
}