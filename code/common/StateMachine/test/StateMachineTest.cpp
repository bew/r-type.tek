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

TEST(StateMachine, StateMachineWithTwoStateLinked)
{
    auto s0 = std::make_shared<state_machine::State<std::string> >("S0");
    auto s1 = std::make_shared<state_machine::State<std::string> >("S1");

    s0->addLink("login", *s1);

    state_machine::StateMachine<std::string> sm;

    sm.addState(s0);
    sm.addState(s1);

    std::string current_state = sm.getInitialState();

    ASSERT_EQ(current_state, s0->getName());

    ASSERT_TRUE(sm[s0->getName()]->has("login"));
    ASSERT_FALSE(sm[s0->getName()]->has("ok"));

    current_state = sm[s0->getName()]->getLink("login");

    ASSERT_EQ(current_state, s1->getName());

    ASSERT_THROW(sm["unknownState"], std::out_of_range);
}

TEST(StateMachine, LoginMachinState)
{
    auto init = std::make_shared<state_machine::State<std::string> >("init");
    auto login = std::make_shared<state_machine::State<std::string> >("login");
    auto signup = std::make_shared<state_machine::State<std::string> >("signup");

    init->addLink("login", *login);

    init->addLink("signup", *signup);

    signup->addLink("ok", *init);

    state_machine::StateMachine<std::string> sm;

    sm.addState(init);
    sm.addState(login);
    sm.addState(signup);

    std::string currentState(sm.getInitialState());

    ASSERT_TRUE(sm[currentState]->has("login"));
    ASSERT_TRUE(sm[currentState]->has("signup"));
    ASSERT_FALSE(sm[currentState]->has("ok"));

    currentState = sm[currentState]->getLink("login");

    ASSERT_EQ(currentState, login->getName());

    ASSERT_EQ(sm[currentState]->getEdges().size(), 0);

    currentState = sm.getInitialState();
    currentState = sm[currentState]->getLink("signup");

    ASSERT_EQ(currentState, signup->getName());

    ASSERT_TRUE(sm[currentState]->has("ok"));

    currentState = sm[currentState]->getLink("ok");

    ASSERT_EQ(currentState, init->getName());
}