/*
 Debounce for RedBear Duo
 Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 a minimum delay between toggles to debounce the circuit (i.e. to ignore
 noise).
 The circuit:
 * internal LED on D7
 * pushbutton attached from D0 to +3V3 (uses internal pulldown)
 created 21 November 2006
 by David A. Mellis for Arduino
 modified 30 Aug 2011
 by Limor Fried
 modified 28 Dec 2012
 by Mike Walters
 modified 29 Aug 2016
 by Bjoern Hartmann for RedBear Duo
 
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/Debounce
 */

// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = D0;    // the number of the pushbutton pin
const int buttonPin1 = D1;    // the number of the pushbutton pin
const int buttonPin2 = D2;    // the number of the pushbutton pin
const int ledPin = D7;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int buttonState1;             // the current reading from the input pin
int buttonState2;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(buttonPin1, INPUT_PULLDOWN);
  pinMode(buttonPin2, INPUT_PULLDOWN);  
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  int reading1 = digitalRead(buttonPin1);  
  int reading2 = digitalRead(buttonPin2);  
  Serial.print(reading);
  Serial.print(reading1);
  Serial.println(reading2);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }  

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        ledState = !ledState;
      }
    }
  }  

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
