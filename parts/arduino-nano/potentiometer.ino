#include <Servo.h>

Servo servo1;  
Servo servo2;  

int potPin1 = A0;  // Analog input pin that the potentiometer1 is attached to
int potPin2 = A1;  // Analog input pin that the potentiometer2 is attached to

void setup() {
  servo1.attach(9);  // attaches the servo1 on pin 9
  servo2.attach(10); // attaches the servo2 on pin 10
}

void loop() {
  int potValue1 = analogRead(potPin1);            // reads the value of the potentiometer1 (value between 0 and 1023)
  int potValue2 = analogRead(potPin2);            // reads the value of the potentiometer2 (value between 0 and 1023)

  int servoPos1 = map(potValue1, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
  int servoPos2 = map(potValue2, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)

  servo1.write(servoPos1);                         // sets the servo position according to the scaled value
  servo2.write(servoPos2);                         // sets the servo position according to the scaled value

  delay(15);                                       // waits for the servo to get there
}
