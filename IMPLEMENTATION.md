# Implementation Tricks

This document aims to provide some useful tricks to implement the BulletJson specification in the best way for your needing.

TODO

- Have in mind that every line of code on the bullet object will run for EVERY bullet on the screen, EVERY frame. Usually will there thousand of bullets on screen, a simple mistake can fuck completely with the game performance.

- If the direction or the speed is not changing, there's no needing of calculate the x/y acceleration per frame, it will return the same value every frame. Just store the values and add it to current the x/y every frame. Actions such as ChangeSpeed or ChangeDirection should recalculate the acceleration during its execution time.

- Allocate and deallocate bullets from the memory can be very expensive, use an instance pool for bullets instead, it can improve drastically the game performance.