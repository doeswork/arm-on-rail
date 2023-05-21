#include <Servo.h>

Servo servo1;
Servo servo2;

int pos1 = 90;
int pos2 = 90;
int relayPin = 3;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  servo1.attach(9);  // Attach servo1 to pin 9
  servo2.attach(10); // Attach servo2 to pin 10
  servo1.write(pos1);
  servo2.write(pos2);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'u':
        pos1 += 5;
        break;
      case 'd':
        pos1 -= 5;
        break;
      case 'l':
        pos2 += 5;
        break;
      case 'r':
        pos2 -= 5;
        break;
      case 'o':
        digitalWrite(relayPin, HIGH);
        break;
      case 'f':
        digitalWrite(relayPin, LOW);
        break;
    }
    pos1 = constrain(pos1, 0, 180);
    pos2 = constrain(pos2, 0, 180);
    servo1.write(pos1);
    servo2.write(pos2);
  }
}
