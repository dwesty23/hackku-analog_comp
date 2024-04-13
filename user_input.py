## sample code

import serial
import time

# Replace 'COM3' with the port to which your Arduino is connected
ser = serial.Serial('COM3', 9600)

try:
    while True:
        # Input from the user in the terminal
        command = input("Enter command (1 to turn on, 0 to turn off): ")
        ser.write(command.encode())  # Send the command to the Arduino
        time.sleep(1)  # Wait a bit for the Arduino to respond
except KeyboardInterrupt:
    ser.close()  # Close the serial connection when Ctrl+C is pressed

## end of sample code