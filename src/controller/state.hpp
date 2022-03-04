#ifndef CONTROLLER_STATE_HPP
#define CONTROLLER_STATE_HPP

#include <string>

#include "handlers.hpp"

namespace controller
{

class state : public handlers
{
public:
    virtual void on_entry(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_exit(const std::shared_ptr<context>& ctx) const = 0;

    virtual std::string get_name() const = 0;
};

}

#endif
