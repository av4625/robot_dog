#include <gtest/gtest.h>

#include <controller/state_store_impl.hpp>

namespace controller
{

namespace
{

class StateStoreTests : public ::testing::Test
{
protected:
    StateStoreTests() : state_store_() {}

    state_store_impl state_store_;
};

class StateStoreStates :
    public StateStoreTests,
    public ::testing::WithParamInterface<std::pair<std::string, state_id> >
{
};

}

TEST_F(StateStoreTests, GetInitialStateWillReturnStateLean)
{
    EXPECT_EQ("lean", state_store_.get_initial_state()->get_name());
}

TEST_F(StateStoreTests, GetStateWithInvalidEnumReturnsStateLean)
{
    EXPECT_EQ(
        "lean",
        state_store_.get_state(static_cast<state_id>(999))->get_name());
}

TEST_P(StateStoreStates, GetStateWillReturnCorrectState)
{
    EXPECT_EQ(
        GetParam().first,
        state_store_.get_state(GetParam().second)->get_name());
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    StateStoreStates,
    ::testing::Values(
        std::make_pair("lean", state_id::lean),
        std::make_pair("trim", state_id::trim)));

}
