#include "AnalogButtons.h"
#include <Arduino.h>

Button::Button(uint16_t value, void (*clickFunction)(void)) {
	this->value = value;
	this->duration = 1000;
	this->interval = 250;
	this->isHeldDown = false;
	this->isClicked = false;
	this->clickFunction = clickFunction;
	this->holdFunction = 0;
}

Button::Button(uint16_t value, void (*clickFunction)(void), void (*holdFunction)(void), uint16_t holdDuration, uint16_t holdInterval) {
	this->value = value;
	this->duration = holdDuration;
	this->interval = holdInterval;
	this->isHeldDown = false;
	this->isClicked = false;
	this->clickFunction = clickFunction;
	this->holdFunction = holdFunction;
}

AnalogButtons::AnalogButtons(uint8_t pin, uint8_t margin) {
	this->pin = pin;
	this->margin = margin;
}

void AnalogButtons::add(Button button) {
	if (buttonsCount < ANALOGBUTTONS_MAX_SIZE) {
    	buttons[buttonsCount++] = button;
  	}
}

void AnalogButtons::check() {
	// In case this function gets called very frequently avoid sampling the analog pin too often: max frequency is 50Hz
		uint16_t reading = analogRead(pin);
		for (uint8_t i = 0; i < buttonsCount; i++) {
			if (reading >= buttons[i].value - margin && reading <= buttons[i].value + margin) {

				if (buttons[i].isClicked == false) {
					buttons[i].pressed();
					previousMillis = millis();
					buttons[i].isClicked = true;

				} else {
					if (buttons[i].isHeldDown == true && ((millis() - previousMillis) > buttons[i].interval)) {
						buttons[i].held();
						previousMillis = millis();
					} else if (buttons[i].isHeldDown != true && ((millis() - previousMillis) > buttons[i].duration)) {
						buttons[i].isHeldDown = true;
						buttons[i].held();
						previousMillis = millis();
					}
				}
				// The first matching button is the only one that gets triggered
				return;
			} else {
				buttons[i].isHeldDown = false;
				buttons[i].isClicked = false;
			}
		}
		// If execution reaches this point then no button has been pressed during this check


}
