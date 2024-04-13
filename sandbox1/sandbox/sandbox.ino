const int analogPin = A0;      // Potentiometer connected to A0
const int outputPin = 9;       // Output pin (DAC)
const int ledPin = 13;         // Onboard LED pin
const float samplingFrequency = 50000.0;  // Sampling frequency (Hz)
float frequency = 1.0;      // Frequency of the sine wave (initially set to 1 Hz)
float phaseIncrement = 0.0;    // Phase increment based on frequency
float phase = 0.0;             // Phase of the sine wave
const int tableSize = 256;     // Size of the sine wave lookup table
int sinTable[tableSize];       // Lookup table for the sine wave

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set the LED pin as output

  // Populate sine wave lookup table
  for (int i = 0; i < tableSize; i++) {
    sinTable[i] = (int)(127.5 * (1 + sin(2 * PI * i / tableSize)));
  }

  // Calculate phase increment based on sampling frequency
  phaseIncrement = 2 * PI * frequency / samplingFrequency;
}

void loop() {
  int analogValue = analogRead(analogPin);
  float frequency = map(analogValue, 0, 1023, 1, 5);  // Map input value to frequency range 1-5 Hz

  for (int i = 0; i < (int)(samplingFrequency / frequency); i++) {
    int sinIndex = (int)(phase * (tableSize / (2 * PI))) % tableSize; // Index into the lookup table
    analogWrite(outputPin, sinTable[sinIndex]); // Output the value from the lookup table

    phase += phaseIncrement;
    if (phase >= 2 * PI) {
      phase -= 2 * PI;
    }
  }

  // Blink logic for LED at maximum and minimum
  if (sin(phase) >= 0.999) { // Close to maximum
    blinkLED(1);
  } else if (sin(phase) <= -0.999) { // Close to minimum
    blinkLED(2);
  }
}

void blinkLED(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(100);                  // Wait 100 milliseconds
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(100);                  // Wait 100 milliseconds
  }
}
