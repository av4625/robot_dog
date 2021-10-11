# Robot Dog

# Dimensions
* Upper leg length: 55mm
* Lower leg length: 55mm
* More as I know them...

# To-Do List
- [x] Make an upper leg
- [x] Make a lower leg
- [x] Position a single foot in Z space (Isosceles Triangle)
- [x] Position a single foot in X space (Right Angled Triangle)
- [x] Buy more servos for more legs
- [ ] Work out exact radians to servo microseconds mapping ranges
- [ ] Add smoothing to servos
- [ ] Add interpolation between movements (Maybe make a public arduino
interpolation library)
- [ ] New upper leg design so that there is some natural compliance at the
joints
- [ ] Make 3 more legs
- [ ] Write code to position all legs independently
- [ ] Make the dogs body
- [ ] Make gait to lift opposite legs
- [ ] Make gait to walk

# Stretch Goals
- [ ] Position a single foot in Y space (Right Angled Triangle). Requires a hip
design for the dog and more servos

# Dependencies
* Conan: Package manager for C++. Used to get GoogleTest for the unit tests
* 8 MG90S servos (12 if the stretch goal of positioning in Y space is met)
* ESP32 38 pin model, with 2 cores wroom-32 (Models with different amounts of
pins, pins may/may not need changed
for other models)
* Power supply for the servos (I use a 2 cell, 7.4v lipo regulated to 6v)
