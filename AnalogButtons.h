/*
 AnalogButtons.h - Multiple buttons on one pin library
 Copyright (c) 2014 Roberto Lo Giacco.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as 
 published by the Free Software Foundation, either version 3 of the 
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ANALOGBUTTONS_H_
#define ANALOGBUTTONS_H_

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

#ifndef ANALOGBUTTONS_SAMPLING_INTERVAL
#define ANALOGBUTTONS_SAMPLING_INTERVAL 20
#endif 

class Button {
	friend class AnalogButtons;
public:
	Button() {};
	/**
	 * Creates an instance representing a single button.
	 *
	 * @param value is the ADC value associated to the voltage reading for this button, will be combined with the `margin` value
	 * @param clickFunction is a reference to the function executed upon button click
	 * @param holdFunction is a reference to the executed upon button hold
	 * @param holdDuration determines the number of milliseconds the button must remain pressed before being identified as held down (defaults to 1 second)
	 * @param holdInterval determines the number of milliseconds between each activation of the *hold function* while the button is kept pressed (defaults to 250 milliseconds)
	 */
	Button(uint16_t value, void (*clickFunction)(void) = 0, void (*holdFunction)(void) = 0, uint16_t holdDuration = 1000, uint16_t holdInterval = 250);

	// Override this function if you want
	inline void pressed() {
		if (clickFunction)
			(*clickFunction)();
	}

	// Override this function if you want
	inline void held() {
		if (holdFunction)
			(*holdFunction)();
		else
			pressed();
	}
private:
	uint16_t value;
	uint32_t duration;
	uint16_t interval;
	boolean isHeldDown;
	void (*clickFunction)(void);
	void (*holdFunction)(void);
};

class AnalogButtons {
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

	Button* debounceButton;

public:
	/**
	 * Creates the instance handling an analog pin to support multiple buttons.
	 *
	 * @param pin the analog pin this instance will manage
	 * @param mode the pin mode (defaults to INPUT)
	 * @param debounce determines the minimum duration a button must remain pressed to be considered being *clicked* in order to avoid false positives (defaults to 5)
	 * @param margin takes into account slight resistance fluctuations and ADC errors transforming the button *value* into a range (defaults to 10)
	 */
	AnalogButtons(uint8_t pin, uint8_t mode = INPUT, uint16_t debounce = 5, uint8_t margin = 10);

	/**
	 * Adds a button to this handler.
	 */
	void add(Button button);

	/**
	 * Must be executed perioodically in order to have the button functions activated accordingly to the button pressed.
	 */
	void check();
};

#endif // ANALOGBUTTONS_H_