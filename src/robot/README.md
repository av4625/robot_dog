# Robot

## Servos

### Shoulder

When the upper leg is pointing straight down from the shoulder the servo is at
45 degrees of rotation. The code treats straight down as 0 degrees. From here it
can move to -45 degrees (clockwise | 500 microseconds) or to 135 degrees (anti
clockwise | 2500 micro seconds). This is because the knee points backwards. More
rotation is needed behind the center line than in front.

### Knee

#### Old Way
When the upper and lower leg are straight, the servo is at 180 degrees. The code
also treats this as 180 degrees.

#### New Way
When the upper and lower leg are straight, the servo is at 150 degrees The code
treats this as 180 degrees. From here it can move -150 degrees to 30 degrees
(lower leg clockwise / upper leg anti clockwise | 2500 microseconds) or to +30
degrees to 210 degrees (lower leg anti clockwise / upper leg clockwise | 0
microseconds)
