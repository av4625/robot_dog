[![Build Status](https://app.travis-ci.com/av4625/robot_dog.svg?branch=master)](https://app.travis-ci.com/av4625/robot_dog)
[![Unittests](https://github.com/av4625/robot_dog/actions/workflows/unittests.yml/badge.svg)](https://github.com/av4625/robot_dog/actions/workflows/unittests.yml)

# Robot Dog

## CAD

### Early Leg Design

Initial design for the leg that I have been using for testing.

![Leg Front](/images/leg_front.png "Leg Front")

![Leg Back](/images/leg_back.png "Leg Back")

### Dimensions
* Upper leg length: 55mm
* Lower leg length: 55mm
* More as I know them...

### To-Do List
- [x] Make an upper leg
- [x] Make a lower leg
- [x] Buy more servos for more legs
- [ ] New upper leg design so that there is some natural compliance at the
joints
- [ ] Make 3 more legs
- [ ] Make the dogs body

## Code

### To-Do List
- [x] Position a single foot in Z space (Isosceles Triangle)
- [x] Position a single foot in X space (Right Angled Triangle)
- [ ] Figure a clean way to add the "trim" or microsecond offset that is
required to move the joints to the zero position
- [ ] Work out exact radians to servo microseconds mapping ranges
- [x] Add smoothing to servos (should get this for free with interpolation and
using an easing out curve like a sine curve)
- [x] Add hal for RAMP library
- [x] Use hal RAMP for interpolation
- [ ] Change max height depending on forward/back amount?
- [ ] Set starting position of robot so we dont have to rely on center joysticks
- [ ] Make calculations mockable so the `two_axis_leg` tests are better (
templated `constrict` holding me back)
- [x] Take the servo pins in the constructor of the leg impls so the interfaces
don't need to know how many pins a specific impl will need in
the begin function?
- [ ] Should dog `set_position` invert the forward back position so that when
you set the dog position forward the body goes forward and the leg goes back?
- [x] Write code to position all legs independently
- [ ] Make gait to lift opposite legs
- [ ] Make gait to walk
- [ ] Statemachine for different modes controlled by the PS4 remote
- [ ] Remove travis integration?

### Stretch Goals
- [ ] Position a single foot in Y space (Right Angled Triangle). Requires a hip
design for the dog and more servos

## Dependencies
* Conan: Package manager for C++. Used to get GoogleTest for the unit tests
* 8 MG90S servos (12 if the stretch goal of positioning in Y space is met)
* ESP32 38 pin model, with 2 cores wroom-32 (Models with different amounts of
pins should work, pins may/may not need changed
for other models)
* Power supply for the servos (I use a 2 cell, 7.4v lipo regulated to 6v)
* 3D Printer
