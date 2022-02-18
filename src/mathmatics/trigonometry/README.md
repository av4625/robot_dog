# Trigonometry

## Isosceles Triangle

                 |\
                 | \
                 |  \
                 |   \
                 |    \
                 |    /
                 |   /
                 |  /
                 | /
                 |/

The top of the triangle is the shoulder joint on the robot. The bottom of the
triangle is the foot of the robot. The top diagonal line is the upper leg. The
bottom diagonal line is the lower leg. The vertical line is the overall leg
length of the robot. The upper and lower leg are the same length which makes
this triangle isosceles. The shoulder and knee angles can be generated if the
overall leg length is known as the upper and lower leg lengths are also known.

## Right Angled Triangle

                /|\
               / | \
              /  |  \
             /   |   \
            /    |    \
           /     |     \
          /      |      \
         /       |       \
        /        |        \
       /_________|_________\

The top of the triangle is the shoulder joint on the robot. The horizonal line
at the bottom is the ground. The foot can be placed anywhere on the ground. The
vertical and diagonal lines are straight lines between possible foot locations
and the shoulder joint. A right angled triangle can be used to get the overall
length that the leg needs to be by calculating the hypotenuse given how far
forward or back the foot is (distance from center on the horizontal line) and
how high we want the robot (vertical line between shoulder and ground). This
leg length can then be used in the isosceles triangle equation to get the
shoulder and knee angles.

To make the foot go forward and back the top angle of the triangle must be
calculated and this can be done with the length of the two short sides (overall
height of the robot and forward or back distance). Once this angle is calculated
it will be added to the shoulder angle of the isosceles triangle to move the
foot forward or back.
