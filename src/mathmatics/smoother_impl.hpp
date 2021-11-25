#ifndef MATHMATICS_SMOOTHER_IMPL_HPP
#define MATHMATICS_SMOOTHER_IMPL_HPP

#include <memory>

#include "smoother.hpp"
#include "../hal/hardware/arduino.hpp"

namespace mathmatics
{

class smoother_impl : public smoother
{
public:
    smoother_impl(
        const std::shared_ptr<hal::hardware::arduino>& arduino,
        uint8_t grain = 10);

    void start(short start, short destination) override;
    short get_value() override;
    bool is_finished() const override;

private:
    const std::shared_ptr<hal::hardware::arduino> arduino_;
    const uint8_t grain_;
    double destination_;
    unsigned long previous_value_time_;
    double previous_smoothed_value_;
    bool finished_;
};

}

#endif
