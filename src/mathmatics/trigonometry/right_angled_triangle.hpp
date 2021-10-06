#ifndef MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_HPP
#define MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_HPP

#include <tuple>

/**
 *   A
 *   |\
 *   | \
 *   |  \
 *   |   \
 *   |    \
 * b |     \ c
 *   |      \
 *   |       \
 *   |        \
 *   |_________\
 *   C    a     B
 */

namespace mathmatics
{
namespace trigonometry
{

class right_angled_triangle
{
public:
    virtual ~right_angled_triangle(){}

    /**
     * @brief Return the 3 angles of a right_angled_triangle <A, B, C> in radians.
     *
     * @param side_a_length - The length of side a.
     * @param side_b_length - The length of side b.
     *
     * @return Tuple containing the the 3 angles: <A, B, C>.
     */
    virtual std::tuple<float, float, float> generate_angles(
        float side_a_length, float side_b_length) const = 0;

    /**
     * @brief Return the length of the hypotenuse.
     *
     * @param side_a_length - The length of side a.
     * @param side_b_length - The length of side b.
     *
     * @return The hypotenuse.
     */
    virtual float calculate_hypotenuse(
        float side_a_length, float side_b_length) const = 0;
};

}
}

#endif
