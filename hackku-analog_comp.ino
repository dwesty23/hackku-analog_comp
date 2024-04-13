// sample code

void setup() {
  Serial.begin(115200); // Start serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) { // Check if there is incoming data
    char received = Serial.read(); // Read the incoming byte
    Serial.print("Received: ");
    Serial.println(received);

    // Example action based on received data
    if (received == '1') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED if '1' is received
    } else if (received == '0') {
      digitalWrite(LED_BUILTIN, LOW); // Turn off LED if '0' is received
    }
  }
}


// end of sample code