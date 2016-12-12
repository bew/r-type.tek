#include "gtest/gtest.h"
#include "AComponent.hh"
#include "ComponentTest.hh"
#include "Entity.hh"
#include "WorldPools.hh"

TEST(WorldPools, GetStuff){
    ECS::Pools::WorldPools pools;
    ECS::Entity::Entity *ptr = nullptr;
    pools >> ptr;
    ASSERT_TRUE(ptr != nullptr);
}

TEST(WorldPools, PutStuff){
    ECS::Pools::WorldPools pools;
    ECS::Entity::Entity *ptr = nullptr;
    pools >> ptr;
    pools << ptr;
    ASSERT_TRUE(ptr == nullptr);
}

TEST(ComponentType, CheckType) {
    ECS::Component::ComponentTest test_comp;
    ASSERT_EQ(test_comp.getType(), ECS::Component::TEST);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
