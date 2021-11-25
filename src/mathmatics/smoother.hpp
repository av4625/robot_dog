#ifndef MATHMATICS_SMOOTHER_HPP
#define MATHMATICS_SMOOTHER_HPP

namespace mathmatics
{

class smoother
{
public:
    virtual ~smoother(){}
    virtual void start(short start, short destination) = 0;
    virtual short get_value() = 0;
    virtual bool is_finished() const = 0;
};

}

#endif
