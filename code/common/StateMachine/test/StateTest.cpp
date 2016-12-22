//
// Created by tookie on 12/22/16.
//

#include "gtest/gtest.h"
#include "State.hpp"

TEST(State, ConstructState)
{
    state_machine::State<std::string> state("s0");

    ASSERT_EQ(state.getEdges().size(), 0);

    ASSERT_FALSE(state.has("salut"));
}
