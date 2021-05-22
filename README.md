# Pferderennen - Horse Racing

This small project takes an arduino and as many stepper motors as you like. The ones I used here are **28BYJ-48** with an **ULN2003** as the motor driver.

However, the motor interface class can be freely derived from to support other motors and drivers. For any additional logic the driver class' init function is called in the beginning.

Pin Setups are stored in the src/config.h header.

Print models and a building documentation are found in track.
