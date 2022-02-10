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
- [x] Try slower max speed for servos or different curve to make movement
smoother, or add an additional smoothing that has a bias for the previous value
as the interpolation doesn't get to use the sine wave to ease out if the inputs
constantly change. Keep interpolation for the gaits.
- [x] Figure out how to make both joints get to the destination angle at the
same time when using smoothing (This might actually happen for free because it
uses percentages)
- [ ] Figure out the relationship in smoothing between the percentage of the
previous value and how long it takes (and how many steps it takes) to get to the
destination
- [ ] Change max height depending on forward/back amount?
- [ ] Set starting position of robot so we dont have to rely on center joysticks
- [ ] Make calculations mockable so the `two_axis_leg` tests are better
(templated `constrict` holding me back)
- [x] Take the servo pins in the constructor of the leg impls so the interfaces
don't need to know how many pins a specific impl will need in
the begin function?
- [ ] Should dog `set_position` invert the forward back position so that when
you set the dog position forward the body goes forward and the leg goes back?
- [x] Write code to position all legs independently
- [x] Make the event callback in `ps4_controller` return optional values, if its
not updated it will return 0 which is not what we want. (No std::optional in
C++14 :cry-face:)
- [ ] Make `set_position ` in `two_axis_leg` default to previous `forward_back`
and previous `height` if new ones aren't provided
- [ ] Make gait to lift opposite legs
- [ ] Make gait to walk
- [ ] Statemachine for different modes controlled by the PS4 remote
- [ ] Remove travis integration?

### Stretch Goals
- [ ] Position a single foot in Y space (Right Angled Triangle). Requires a hip
design for the dog and more servos
- [ ] Add an event loop so that it is easier to control what happens on what
cores. Currently the gamepad calls a callback with the updated values, the
callback sets atomic variables that then are read by core `1`. This is abit
"nasty" but if I call the leg/robot/controller functions in the callback they
will be executed on core one, possibly slowing down reading from the gamepad.

## Dependencies
* Conan: Package manager for C++. Used to get GoogleTest for the unit tests
* 8 MG90S servos (12 if the stretch goal of positioning in Y space is met)
* ESP32 38 pin model, with 2 cores wroom-32 (Models with different amounts of
pins should work, pins may/may not need changed
for other models)
* Power supply for the servos (I use a 2 cell, 7.4v lipo regulated to 6v)
* 3D Printer

## Thoughts
* Have a global shared pointer to a manager that is a state machine. Different
states would be different "modes".
    * Mode for triming servos to correct angle.
    * Mode for leaning.
    * Mode for walking.
    * Etc
* Simple Version
    * On PS4 controller event call through to the manager with the event.
        * This will happen on core `0` as the PS4 controller events run there.
    * On core `1` continually call update on the robot.
    * Need to think whether the manager/dog/leg/interpolation/servo will be
    happy with this happening on 2 cores. Semaphore?
* Save to Atomic Variables
    * Have atomic variables for stick position etc and only call through to
    control the robot on core `1` using the atomic variables that would be set
    from core `0`.
* Event Loop
    * Have an event loop (or 2) to run things on specific cores.
    * Have event loop on core `1` at a higher priority than the updating robot
    task. Then when an interesting controller event happens, post the call on
    the event loop. Core `1` can't run two things in parallel so theres no
    worries about "strange" things happening. Need to make sure that the event
    executes the events quickly even with the updating task being quite busy.
