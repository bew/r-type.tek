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

TEST(State, LinkTwoState)
{
    state_machine::State<std::string> state0("s0");
    state_machine::State<std::string> state1("s1");

    state0.addLink("login", state1);

    ASSERT_TRUE(state0.has("login"));

    ASSERT_EQ(state0.getEdges().size(), 1);

    ASSERT_EQ(state0.getLink("login"), state1.getName());
}

TEST(State, StateMultipleLink)
{
    state_machine::State<std::string> init("s0");
    state_machine::State<std::string> login("s1");
    state_machine::State<std::string> signup("s2");

    init.addLink("login", login);
    init.addLink("signup", signup);

    signup.addLink("ok", init);

    ASSERT_TRUE(init.has("login"));
    ASSERT_TRUE(init.has("signup"));
    ASSERT_FALSE(init.has("ok"));

    ASSERT_TRUE(signup.has("ok"));

    ASSERT_EQ(init.getEdges().size(), 2);

    ASSERT_EQ(signup.getEdges().size(), 1);

    ASSERT_EQ(login.getEdges().size(), 0);

    ASSERT_EQ(init.getLink("login"), login.getName());
    ASSERT_EQ(init.getLink("signup"), signup.getName());

    ASSERT_EQ(signup.getLink("ok"), init.getName());

    ASSERT_THROW(login.getLink("signup"), std::out_of_range);
}