
#include "gtest/gtest.h"
#include "AComponent.hh"
#include "ComponentTest.hh"
#include "Entity.hh"

TEST(ComponentType, CheckType) {
    ECS::Component::ComponentTest test_comp;
    ASSERT_EQ(test_comp.getType(), ECS::Component::TEST);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
