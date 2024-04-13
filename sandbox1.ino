#include <Arduino.h>

const int analogPin = A0;   // Potentiometer connected to A0
const int outputPin = 9;    // Output pin (PWM)
const int ledPin = 13;      // Onboard LED pin
float phase = 0.0;          // Phase of the sine wave
float frequency = 1.0;      // Frequency of the sine wave (initially set to 1 Hz)
float previousSineValue = 0.0;  // To track changes in sine value

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set the LED pin as output
}

void loop() {
  int analogValue = 1; // For initial testing, set to a fixed value
  frequency = map(analogValue, 0, 1023, 1, 5);    // Map input value to frequency range 1-5 Hz

  float sineValue = sin(phase);                   // Calculate sine value from phase
  int pwmValue = map((sineValue * 127.5) + 127.5, 0, 255, 0, 255);  // Convert sine to PWM
  analogWrite(outputPin, pwmValue);               // Output the PWM signal to pin

  // Blink logic for LED at maximum and minimum
  if (sineValue >= 0.999 && previousSineValue < 0.999) { // Close to maximum
    blinkLED(1);
  } else if (sineValue <= -0.999 && previousSineValue > -0.999) { // Close to minimum
    blinkLED(2);
  }

  previousSineValue = sineValue; // Update previous sine value for next comparison

  phase += 2 * PI * frequency / 1000;             // Increase phase based on frequency and time
  if (phase >= 2 * PI) {                          // Reset phase after completing a cycle
    phase -= 2 * PI;
  }

  delay(1);                                       // Small delay to stabilize output
}

void blinkLED(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(100);                  // Wait 100 milliseconds
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(100);                  // Wait 100 milliseconds
  }
}

