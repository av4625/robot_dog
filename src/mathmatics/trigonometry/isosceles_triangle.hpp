#ifndef MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_HPP
#define MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_HPP

#include <tuple>

/**
 *   A
 *   |\
 *   | \
 *   |  \ b
 *   |   \
 * c |    \ C
 *   |    /
 *   |   /
 *   |  / a
 *   | /
 *   |/
 *   B
 */

namespace mathmatics
{
namespace trigonometry
{

class isosceles_triangle
{
public:
    virtual ~isosceles_triangle(){}

    /**
     * @brief Return the 3 angles of a isosceles_triangle <A, B, C> in radians.
     *
     * @param side_c_length - The length of side c.
     *
     * @return Tuple containing the the 3 angles: <A, B, C>.
     */
    virtual std::tuple<float, float, float> generate_angles(
        float side_c_length) const = 0;
};

}
}

#endif
