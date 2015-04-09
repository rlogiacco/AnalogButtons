#include "AnalogButtons.h"
#include <Arduino.h>

Analog::Button::Button(uint16_t value, void (*clickFunction)(void), void (*holdFunction)(void), uint16_t holdDuration, uint16_t holdInterval) {
	this->value = value;
	this->duration = holdDuration;
	this->interval = holdInterval;
	this->clickFunction = clickFunction;
	this->holdFunction = holdFunction;
}

Analog::Buttons::Buttons(uint8_t pin, uint16_t debounce, uint8_t margin) {
	this->pin = pin;
	this->debounce = debounce;
	this->counter = 0;
	this->margin = margin;
}

void Analog::Buttons::add(Button button) {
	if (buttonsCount < ANALOGBUTTONS_MAX_SIZE) {
		buttons[buttonsCount++] = button;
	}
}

void Analog::Buttons::check() {
	// In case this function gets called very frequently avoid sampling the analog pin too often: max frequency is 50Hz
	if (millis() - time > 120) {
		time = millis();
		uint16_t reading = analogRead(pin);
		for (uint8_t i = 0; i < buttonsCount; i++) {
			if (reading >= buttons[i].value - margin && reading <= buttons[i].value + margin) {
				
				if (lastButtonPressed != &buttons[i]) {
					if (++counter >= debounce) {
						lastButtonPressed = &buttons[i];
						counter = 0;
						buttons[i].pressed();
						previousMillis = millis();
					}
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
			}
		}
		// If execution reaches this point then no button has been pressed during this check
		lastButtonPressed = 0;
	}
}
