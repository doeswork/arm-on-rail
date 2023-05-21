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

# Replace '/dev/ttyACM0' with the appropriate port for your Arduino
arduino = serial.Serial('/dev/ttyUSB0', 9600) #ttyUSB0
time.sleep(2)  # Give time for the connection to initialize

relayStatus = False

print("Press 'q' to quit")
while True:
    key = getch()
    if key == 'q':
        break
    elif key == ' ':  # Space bar
        if relayStatus:
            arduino.write(b'f')
        else:
            arduino.write(b'o')
        relayStatus = not relayStatus
    elif key == '\x1b':  # Check for arrow key escape sequence
        key = getch()
        if key == '[':
            key = getch()
            if key == 'A':  # Up arrow
                arduino.write(b'u')
            elif key == 'B':  # Down arrow
                arduino.write(b'd')
            elif key == 'C':  # Right arrow
                arduino.write(b'r')
            elif key == 'D':  # Left arrow
                arduino.write(b'l')

arduino.close()
