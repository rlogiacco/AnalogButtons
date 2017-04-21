#include <AnalogButtons.h>

#define ANALOG_PIN A1

// A call back function that you pass into the constructor of AnalogButtons, see example
// below. Alternativly you could extend the Button class and re-define the methods pressed() 
// or held() which are called 
void b1Click() {  
    Serial.print("button 1 clicked"); 
}

void b2Click() {  
    Serial.print("button 2 clicked"); 
}
void b2Hold() {  
    Serial.print("button 2 held"); 
}

void b3Click() {  
    Serial.print("button 3 clicked"); 
}
void b3Hold() {  
    Serial.print("button 3 held"); 
}

void b4Click() {  
    Serial.print("button 4 clicked"); 
}
void b4Hold() {  
    Serial.print("button 4 held"); 
}

void b5Click() {  
    Serial.print("button 5 clicked"); 
}
void b5Hold() {  
    Serial.print("button 5 held"); 
}

AnalogButtons analogButtons(ANALOG_PIN, INPUT);
Button b1 = Button(1013, &b1Click);
Button b2 = Button(1002, &b2Click, &b2Hold);
Button b3 = Button(970, &b3Click, &b3Hold);
// Default hold activation frequency of 250ms is overriden for button 4 so to 
// get it activated (hold function invoked) only every 500ms
Button b4 = Button(929, &b4Click, &b4Hold, 1000, 500);
// Default hold duration is 1 second, lets make it 5 seconds for button5
Button b5 = Button(860, &b5Click, &b5Hold, 5000);

void setup() {
  Serial.begin(9600); 
  Serial.println("Testing your Analog buttons");
  
  analogButtons.add(b1);
  analogButtons.add(b2);
  analogButtons.add(b3);
  analogButtons.add(b4);
  analogButtons.add(b5);  
 }
 
void loop() {  
  // To check values when button are pressed
  analogButtons.check();
  
  // To configure the MAX/Min values for each button: 
  // uncomment the following line and make sure you've called Serial.begin(9600) 
  // Then in turn hold down each button, noting down the max/min values
  
  //configure();
}

void configure() {
	unsigned int value = analogRead(ANALOG_PIN);
	Serial.println(value);
	delay(250);
}
