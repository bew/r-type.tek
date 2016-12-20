//
// Created by tookie on 12/20/16.
//

#include "gtest/gtest.h"
#include "CompLife.hh"

TEST(Flags, DefaultFlags)
{
    ECS::Component::AComponent* life = new ECS::Component::CompLife(100);

    bool isSerializable = life->isFlagged(ECS::Component::SERIALIZABLE_MASK);

    delete(life);

    ASSERT_FALSE(isSerializable);
}

TEST(Flags, addFlag)
{
    ECS::Component::AComponent* life = new ECS::Component::CompLife(100);

    life->addFlag(1);

    bool isSerializable = life->isFlagged(ECS::Component::SERIALIZABLE_MASK);

    delete(life);

    ASSERT_TRUE(isSerializable);
}

TEST(Flags, DeleteFlag)
{
    ECS::Component::AComponent* life = new ECS::Component::CompLife(100);

    life->addFlag(1);

    bool isSerializable = life->isFlagged(ECS::Component::SERIALIZABLE_MASK);

    ASSERT_TRUE(isSerializable);

    life->unFlag(~ECS::Component::SERIALIZABLE_MASK);

    isSerializable = life->isFlagged(ECS::Component::SERIALIZABLE_MASK);

    delete(life);

    ASSERT_FALSE(isSerializable);
}