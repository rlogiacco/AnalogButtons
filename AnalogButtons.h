#ifndef __ANALOGBUTTONS_H
#define __ANALOGBUTTONS_H

/*
 AnalogButtons

 In order to reduce the number of pins used by some projects, sketches can use
 this library to wire multiple buttons to one single analog pin.
 You can register a call-back function which gets called when a button is
 pressed or held down for the defined number of seconds.

 Minimum hold duration (time that must elapse before a button is considered
 being held) and hold interval (time that must elapse between each activation
 of the hold function) can both be configured.

 By default max number of buttons per pin is limited to 5 for memory
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
#define ANALOGBUTTONS_MAX_SIZE 5
#endif

class Button {
public:
	uint16_t value;

	// hold information
	uint32_t duration;
	uint16_t interval;
	boolean isHeldDown;
	boolean isClicked;

	Button() {};
	Button(uint16_t value, void (*clickFunction)(void));
	Button(uint16_t value, void (*clickFunction)(void), void (*holdFunction)(void), uint16_t holdDuration, uint16_t holdInterval);

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




class AnalogButtons {
private:
	uint32_t previousMillis;
	uint8_t margin;

	// AnalogPin
	uint8_t pin;

	uint8_t buttonsCount;
	Button buttons[ANALOGBUTTONS_MAX_SIZE];

public:
	AnalogButtons(uint8_t pin, uint8_t margin = 10);

	void add(Button button);

	void check();
};

#endif
