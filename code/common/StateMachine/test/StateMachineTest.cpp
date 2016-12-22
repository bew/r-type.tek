//
// Created by tookie on 12/22/16.
//

#include "StateMachine.hpp"
#include "gtest/gtest.h"

TEST(StateMachine, SimpleStateMachineWithOneState)
{
    auto s0 = std::make_shared<state_machine::State<std::string> >("S0");

    state_machine::StateMachine<std::string> sm;

    sm.addState(s0);

    ASSERT_EQ("S0", sm.getInitialState());

    ASSERT_EQ(s0, sm[s0->getName()]);
}
