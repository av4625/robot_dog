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
        int max_out_range) const;

    template<typename T>
    T constrict(T value, T minimum, T maximum) const
    {
        return (value < minimum) ? minimum : ((value > maximum) ? maximum : value);
    }
};

}

#endif
