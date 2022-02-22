#ifndef MATHMATICS_CALCULATIONS_HPP
#define MATHMATICS_CALCULATIONS_HPP

namespace mathmatics
{

class calculations
{
public:
    virtual ~calculations(){}

    virtual float map(
        float in,
        float min_in_range,
        float max_in_range,
        int min_out_range,
        int max_out_range) const = 0;

    virtual short constrict(
        short value, short minimum, short maximum) const = 0;

    virtual int constrict(int value, int minimum, int maximum) const = 0;

    virtual double constrict(
        double value, double minimum, double maximum) const = 0;
};

}

#endif
