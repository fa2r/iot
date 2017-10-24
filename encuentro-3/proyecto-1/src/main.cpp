#include <Arduino.h>

const int ledPin    = 2;
const int buttonPin = 4;
const int buzzerPin = 9;
const int lightPin  = 13;
const int ldrPin    = A0;
const int tempPin   = A4;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long lastLdrTime = 0;
const unsigned long ldrDelay = 1000;

float temp = 25;
unsigned long lastTempTime = 0;
const unsigned long tempDelay = 5000;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void play() {
  playTone(200, 100);
  playTone(400, 100);
}

int button() {
  int res = 0;
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        Serial.println("button");
        res = 1;
      }
    }
  }
  lastButtonState = reading;
  return res;
}


void ldr() {
   if ((millis() - lastLdrTime) > ldrDelay) {
     int ldr = analogRead(ldrPin);
     Serial.print("ldr ");
     Serial.println(ldr);
     lastLdrTime = millis();
   }
}

void temperature() {
  int value = analogRead(tempPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10;

  temp = 0.99 * temp + 0.01 * celsius;

  if ((millis() - lastTempTime) > tempDelay) {
    Serial.print("temp ");
    Serial.println(temp);
    lastTempTime = millis();
  }

}

void processSerialInput() {
  if (Serial.available()!=0) {
    String command;
    command = Serial.readString();
    if (command.startsWith("play")) {
      play();
    }
    if (command.startsWith("ledOn")) {
      digitalWrite(ledPin, HIGH);
    }
    if (command.startsWith("ledOff")) {
      digitalWrite(ledPin, LOW);
    }
    if (command.startsWith("lightOn")) {
      digitalWrite(lightPin, HIGH);
    }
    if (command.startsWith("lightOff")) {
      digitalWrite(lightPin, LOW);
    }
  }
}


/**
 *  Setup
 */
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(tempPin, INPUT);

  Serial.setTimeout(100);
  Serial.begin(9600);
}

/**
 *  The loop function runs over and over again forever
 */
void loop() {

  button();

  ldr();

  temperature();

  processSerialInput();

}
