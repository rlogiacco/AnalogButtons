AnalogButtons [![Build Status](https://travis-ci.org/rlogiacco/AnalogButtons.svg?branch=master)](https://travis-ci.org/rlogiacco/AnalogButtons)
=============

In order to reduce the number of pins used by some projects, sketches can use this library to wire multiple buttons to one single analog pin.

You can register a call-back function which gets called when a button is pressed or held down for the defined number of seconds.

Includes a software simple de-bouncing algorithm which can be tweaked and is based on the max sampling frequency of 50Hz (one sample every 20ms)
 
Minimum hold duration (time that must elapse before a button is considered being held) and hold interval (time that must elapse between each activation of the hold function) can both be configured.

By default max number of buttons per pin is limited to 8 to limit memory consumption, but it can be controlled defining the `ANALOGBUTTONS_MAX_SIZE` macro ***before*** including this library.

Starting from version `1.2.0`:

* the maximum sampling frequency can be controlled defining the `ANALOGBUTTONS_SAMPLING_INTERVAL` macro, defaulting to 20
* holding a button does not imply a *click* event being fired, greatly simplifying writing complex user interfaces 

This work is largely inspired by the AnalogButtons library available in the Arduino Playground library collection, but it represents a substantial improvement in terms of code organization as each operation is going to be defined in a separate function removing the need to determine (through `if` or `switch` statements) which button has been pressed/held.

Contributions are welcome under the [Apache Public License version 2.0 (http://www.apache.org/licenses/LICENSE-2.0.html).

For wiring instructions please refer to the [sample schematics] (https://raw.githubusercontent.com/rlogiacco/AnalogButtons/master/schematic.png) or, if you prefer, to the [sample breadboard] (https://raw.githubusercontent.com/rlogiacco/AnalogButtons/master/breadboard.png).

Also a test rig is available on [Autodesk Circuits] (https://circuits.io/circuits/4718116-analogbuttons) to play with the code and experiment with alternative layouts.

Usage
============

Basically the library usage can be divided into the following four steps. 

1. Buttons definition
---------------------

Each button is defined in isolation in terms of:

* an associated `value` (an unsigned 10 bits integer in the [0-1023] range)
* a `click function` executed upon button click
* an `hold function` executed once the button is identified as *being held* (defaults to click function)
* an `hold duration` determining the number of milliseconds the button must remain pressed before being identified as held down (defaults to 1 second)
* an `hold interval` determining the number of milliseconds between each activation of the *hold function* while the button is kept pressed (defaults to 250 milliseconds)

In its simplest form, a button definition resemble something like the following which defines a button with only a click function.

```
void aButtonClick() {
  // do something
}
Button aButton = Button(512, &aButtonClick);
```

In its most evoluted form a button definition looks like the following.


```
void aButtonClick() {
  // do something
}
void aButtonHold() {
  // do something else
}
Button aButton = Button(512, &aButtonClick, &aButtonHold, 5000, 50);
```


2. Analog pin definition
------------------------

Because buttons will share the same analog pin some configuration is required in order to distinguish and manage the different buttons:

* the `analog pin` the buttons will be attached to
* the `debounce frequency multiplier` which determines the minimum duration a button must remain pressed to be considered being *clicked* in order to avoid false positives (defaults to 5)
* the `analog value margin` which takes into account slight resistance fluctuations and ADC errors transforming the button *value* into a range (defaults to 10)

```
AnalogButtons analogButtons = AnalogButtons(A2);
```

3. Setup
------------------------

Once you have everything defined you need to link everything up, more than probably within your `setup()` function:

```
analogButtons.add(aButton);
analogButtons.add(anotherButton);
```


4. Periodic verification
------------------------

Now all you need is to periodically activate the analog buttons verification which checks the analog pin to determine if one of the many possible conditions occurred and fires the corresponding code. The following code goes into the `loop()` fnction and needs to be executed quite often so don't introduce any `delay(...)` otherwise it will not work as expected: 

```
analogButtons.check();
```
