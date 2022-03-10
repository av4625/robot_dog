#include "state_store_impl.hpp"
#include "state_lean.hpp"
#include "state_trim.hpp"

namespace controller
{

state_store_impl::state_store_impl() :
    lean_(new state_lean()),
    trim_(new state_trim())
{
}

state* state_store_impl::get_initial_state() const
{
    return get_state(state_id::lean);
}

state* state_store_impl::get_state(const state_id id) const
{
    switch (id)
    {
        case state_id::lean:
        {
            return lean_.get();
        }
        case state_id::trim:
        {
            return trim_.get();
        }
        default:
        {
            return lean_.get();
        }
    }
}

}
