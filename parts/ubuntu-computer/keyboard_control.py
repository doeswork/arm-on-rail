import serial
import sys
import time
import tty
import termios

def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# Set up the serial connection
print("Setting up serial connection...")
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Change this to the appropriate port for your Arduino Nano
time.sleep(2)  # Wait for the connection to be established

# Check if the serial connection is open
if ser.isOpen():
    print("Serial connection established!")
else:
    print("Failed to establish serial connection.")
    sys.exit()

# Control the stepper motor with the keyboard
print("Press '1' and '2' to control the stepper motor. '7' and '8' for the servo. Press 'q' to exit.")
while True:
    key_name = getch()
    if key_name == 'q':
        break
    elif key_name == '1':
        ser.write(b'R')
        print("Sent 'R' command for Right rotation")
    elif key_name == '2':
        ser.write(b'L')
        print("Sent 'L' command for Left rotation")
    elif key_name == '7':
        ser.write(b'7')
        print("Sent '7' command to turn the servo left")
    elif key_name == '8':
        ser.write(b'8')
        print("Sent '8' command to turn the servo right")

# Close the serial connection
print("Closing serial connection...")
ser.close()

# Check if the serial connection is closed
if not ser.isOpen():
    print("Serial connection closed!")
else:
    print("Failed to close serial connection.")
