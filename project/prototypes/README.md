## Description
This directory contains demo programs that demonstrate basic I/O using timer and button interrupts.

Program Description
Button P1: Activates both LEDs simultaneously.
Button P2.0: Toggles the red LED on and off.
Button P2.1: Turns the green LED on when pressed (off otherwise).
Button P2.2:
-c Configuration: Cycles the red LED between bright and dim states (requires prior press of P1).
-s Configuration: Gradually increases the brightness of the red LED.
Button P2.3: Generates a sound using the buzzer.

## How to Use

make load-c Configuration:
Implements red LED dimming in C.
make load-s Configuration:
Implements red LED brightening in assembly.
