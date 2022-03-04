#ifndef CONTROLLER_STATE_STORE_IMPL_HPP
#define CONTROLLER_STATE_STORE_IMPL_HPP

#include <memory>

#include "state_store.hpp"

namespace controller
{

class state_store_impl : public state_store
{
public:
    state_store_impl();

    state* get_initial_state() const override;

    state* get_state(state_id id) const override;

private:
    const std::unique_ptr<state> lean_;
    const std::unique_ptr<state> trim_;
};

}

#endif
