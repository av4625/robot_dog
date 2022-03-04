#ifndef CONTROLLER_STATE_STORE_MOCK_HPP
#define CONTROLLER_STATE_STORE_MOCK_HPP

#include <gmock/gmock.h>
#include <controller/state_store.hpp>

namespace controller
{

class state_store_mock : public state_store
{
public:
    MOCK_METHOD(state*, get_initial_state, (), (const, override));
    MOCK_METHOD(state*, get_state, (state_id id), (const, override));
};

}

#endif
