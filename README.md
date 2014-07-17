AnalogButtons
=============

In order to reduce the number of pins used by some projects, sketches can use this library to wire multiple buttons to one single analog pin.

You can register a call-back function which gets called when a button is pressed or held down for the defined number of seconds.

Includes a software key simple de-bouncing algorithm which can be tweaked and is based on the max sampling frequency of 50Hz (one sample every 120ms)
 
Minimum hold duration (time that must elapse before a button is considered being held) and hold interval (time that must elapse between each activation of the hold function) can both be configured.

By default max number of buttons per pin is limited to 8 to limit memory consumption, but it can be controlled defining the ANALOGBUTTONS_MAX_SIZE macro _before_ including this library.

This work is largely inspired by the AnalogButtons library available in the Arduino Playground library collection, but it represents a substantial improvement in terms of code organization as each operation is going to be defined in a separate function removing the need to determine (through *if* or *switch* statements) which button has been pressed/held.

Contributions are welcome under the Apache Public License version 2.

For wiring instructions please refer to the sample schematics in schematic.png.