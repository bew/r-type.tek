
#include "gtest/gtest.h"
#include "AComponent.hh"
#include "CompMovement.hh"
#include "Entity.hh"

TEST(ComponentType, CheckType) {
    ECS::Component::CompMovement test_comp;
    ASSERT_EQ(test_comp.getType(), ECS::Component::MOVEMENT);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
