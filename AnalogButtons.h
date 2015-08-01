#ifndef __ANALOGBUTTONS_H
#define __ANALOGBUTTONS_H

/*
 AnalogButtons

 In order to reduce the number of pins used by some projects, sketches can use
 this library to wire multiple buttons to one single analog pin.
 You can register a call-back function which gets called when a button is
 pressed or held down for the defined number of seconds.
 Includes a software key de-bouncing simple algorithm which can be tweaked and
 is based on the max sampling frequency of 50Hz (one sample every 120ms)
 
 Minimum hold duration (time that must elapse before a button is considered
 being held) and hold interval (time that must elapse between each activation
 of the hold function) can both be configured.

 By default max number of buttons per pin is limited to 8 for memory
 consumption reasons, but it can be controlled defining the
 ANALOGBUTTONS_MAX_SIZE macro _before_ including this library.

 This work is largely inspired by the AnalogButtons library available in the
 Arduino Playground library collection.

 */
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef ANALOGBUTTONS_MAX_SIZE
#define ANALOGBUTTONS_MAX_SIZE 8
#endif 

namespace Analog {

class Button {
public:
	uint16_t value;

	// hold information
	uint32_t duration;
	uint16_t interval;
	boolean isHeldDown;

	Button() {};
	Button(uint16_t value, void (*clickFunction)(void) = 0, void (*holdFunction)(void) = 0, uint16_t holdDuration = 1000, uint16_t holdInterval = 250);

	// Override these function if you want
	inline void pressed() {
		if (clickFunction)
			(*clickFunction)();
	}

	// Override these function if you want
	inline void held() {
		if (holdFunction)
			(*holdFunction)();
		else
			pressed();
	}
private:
	void (*clickFunction)(void);
	void (*holdFunction)(void);
};

class Buttons {
private:
	uint32_t previousMillis;
	uint16_t debounce;
	uint32_t time;
	uint8_t counter;
	uint8_t margin;

	// AnalogPin
	uint8_t pin;

	uint8_t buttonsCount;
	Button buttons[ANALOGBUTTONS_MAX_SIZE];


	// last button pressed
	Button* lastButtonPressed;

public:
	Buttons(uint8_t pin, uint16_t debounce = 5, uint8_t margin = 10);

	void add(Button button);

	void check();
};

} // end namespace Analog

#endif
