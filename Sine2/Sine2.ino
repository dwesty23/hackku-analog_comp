#include <SPI.h>

const int chipSelectPin = 10; // Chip select pin for SPI communication
const int ledPin = 13;        // Onboard LED pin
const float desiredFrequency = 50.0; // Desired frequency of the sine wave (Hz)
const int dacResolution = 12; // DAC resolution (bits)
const float dacMaxVoltage = 3.3; // Maximum output voltage of the DAC (V)
const unsigned long blinkInterval = 1000; // Blink interval in milliseconds

// Function to initialize SPI communication
void initSPI() {
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH); // Disable SPI communication initially
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV64); // Adjust as needed for your DAC
}

// Function to output a value to the DAC
void outputDAC(int value) {
  digitalWrite(chipSelectPin, LOW); // Enable SPI communication
  SPI.transfer16(value);             // Send value over SPI (assuming 16-bit DAC)
  digitalWrite(chipSelectPin, HIGH); // Disable SPI communication
}

void setup() {
  initSPI();
  pinMode(ledPin, OUTPUT); // Initialize LED pin as output
}

void loop() {
  static unsigned long previousMillis = 0;
  static boolean ledState = LOW;

  unsigned long currentMillis = millis();

  // Blink LED at specified interval
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  // Generate sine wave
  const int numSamplesPerPeriod = 100;
  const float phaseIncrement = 2 * PI / numSamplesPerPeriod;
  float phase = 0.0;

  for (int i = 0; i < numSamplesPerPeriod; i++) {
    float sinValue = sin(phase);
    int dacValue = map(sinValue, -1.0, 1.0, 0, pow(2, dacResolution) - 1);
    outputDAC(dacValue);

    // Update phase
    phase += phaseIncrement;
  }
}
