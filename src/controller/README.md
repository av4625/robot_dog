# Robot Dog Controller

## Description
The `controller` is a state machine that handlers for different control events.
Like when a button is pressed or when a joystick is moved. It is a state machine
because there will be different modes. If the dog is in a `lean` mode the
joysticks will make the dog lean in different directions. If it is in a `trim`
mode, you could swap between joints and trim them with a button on the
`controller`. etc.

## Issues
One of the issues with this is that the `gamepad` `controller` class will be a
hal implementation. It will be stored in a `shared_ptr`. It is event driven
under the hood. So the cleanest way would be to hand the hal, handlers to the
`controller` as function pointers and using `shared_from_this` or constructing
the hal with a `shared_ptr` to the `controller` and when an event is triggered
from the `gamepad` the hal would call the right `controller` function.

That is all fine, but ideally we want the `controller` (which would be stored in
a smart pointer, probably a `shared_ptr`) to be able to change the lights on the
`controller` and use the rumble feature. This means that the `controller`
statemachine would need to be contructed with the `gamepad` hal. The issue is
that both the `controller` and `gamepad` hal would have a `shared_ptr` to each
other :(. Meaning that they can never destruct themselves.

### Fixes
* One fix would be for the `controller` to still be constructed with a
`shared_ptr` to the `gamepad` hal and the `gamepad` hal would store the
`controller` in a `weak_ptr`.
* Another way would be to use an event loop. The `controller` and `gamepad` hal
wouldn't store each other. But they would post to the event loop and then the
event loop would call the correct functions depending on subscriptions. A
downside to this is that it would tie it to only ESP32's (I think, maybe not?
Arduino has a library called `Eventually`).
