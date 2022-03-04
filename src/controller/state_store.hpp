#ifndef CONTROLLER_STATE_STORE_HPP
#define CONTROLLER_STATE_STORE_HPP

#include "state.hpp"
#include "state_id.hpp"

namespace controller
{

class state_store
{
public:
    virtual ~state_store(){}

    virtual state* get_initial_state() const = 0;

    virtual state* get_state(state_id id) const = 0;
};

}

#endif
