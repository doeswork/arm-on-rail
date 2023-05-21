import serial
import time

# Replace '/dev/ttyUSB0' with the appropriate port for your Arduino
arduino = serial.Serial('/dev/ttyUSB0', 9600) 
time.sleep(2)  # Give time for the connection to initialize

# Send initial positions for both servos
initial_pos1 = 90
initial_pos2 = 90

for i in range(17):  # each step corresponds to 5 degrees
    arduino.write(b'u')  # Increase position of servo1
    time.sleep(0.05)  # Wait a bit for the servo to get there
time.sleep(1)  # Wait a bit

for i in range(16):  # each step corresponds to 5 degrees
    arduino.write(b'l')  # Increase position of servo2
    time.sleep(0.05)  # Wait a bit for the servo to get there
time.sleep(1)  # Wait a bit

# Activate relay again
arduino.write(b'o')  # Switch relay on
time.sleep(1)  # Wait a bit

for i in range(2):  # each step corresponds to 5 degrees
    arduino.write(b'r')  # Increase position of servo2
    time.sleep(0.05)  # Wait a bit for the servo to get there
time.sleep(1)  # Wait a bit



# Send position for servo1 to 10 degrees
for i in range(12):  # each step corresponds to 5 degrees
    arduino.write(b'd')  # Decrease position of servo1
    time.sleep(0.05)  # Wait a bit for the servo to get there

for i in range(2):  # each step corresponds to 5 degrees
    arduino.write(b'l')  # Increase position of servo2
    time.sleep(0.05)  # Wait a bit for the servo to get there
time.sleep(1)  # Wait a bit

# # Send position for servo2 to 180 degrees
# for i in range(18):  # each step corresponds to 5 degrees
#     arduino.write(b'l')  # Increase position of servo2
#     time.sleep(0.5)  # Wait a bit for the servo to get there
time.sleep(1)  # Wait a bit

arduino.write(b'f')  # Switch relay off
time.sleep(1)  # Wait a bit


arduino.close()
