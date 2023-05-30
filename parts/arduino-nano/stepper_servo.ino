#include <Servo.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define RELAY_PIN 12  // Relay connected on pin 12
int Steps = 0;
boolean Direction = true; // True: Clockwise, False: Counter-Clockwise
int stepsPerCommand = 4096; // Number of steps to take per command

Servo myservo1;  // Create first servo object
Servo myservo2;  // Create second servo object
int pos1 = 0;    // Variable to store the servo1 position
int pos2 = 0;    // Variable to store the servo2 position

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Ensure relay is off to start
  myservo1.attach(6); // Attaches the first servo on pin 6
  myservo2.attach(7); // Attaches the second servo on pin 7
}


void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'R') {
      Direction = true;  // Set direction to clockwise
      for(int i=0; i<stepsPerCommand; i++){
        stepper(1);
        delayMicroseconds(800);
      }
    } else if (command == 'L') {
      Direction = false; // Set direction to counter-clockwise
      for(int i=0; i<stepsPerCommand; i++){
        stepper(1);
        delayMicroseconds(800);
      }
    } else if (command == '7') {
      pos1 = max(0, pos1 - 15); // Decrease servo position
      myservo1.write(pos1);
    } else if (command == '8') {
      pos1 = min(180, pos1 + 15); // Increase servo position
      myservo1.write(pos1);
    }
    else if (command == '4') {
      pos2 = max(0, pos2 - 15); // Decrease second servo position
      myservo2.write(pos2);
    } else if (command == '5') {
      pos2 = min(180, pos2 + 15); // Increase second servo position
      myservo2.write(pos2);
    } else if (command == '6') {
      // Toggle the relay state
      if (digitalRead(RELAY_PIN) == HIGH) {
        digitalWrite(RELAY_PIN, LOW);  // Turn off relay
      } else {
        digitalWrite(RELAY_PIN, HIGH); // Turn on relay
      }
    }
  }
}


void stepper(int xw) {
  for (int x = 0; x < xw; x++) {
    switch (Steps) {
      case 0:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      case 1:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        break;
      case 2:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 3:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;
      case 4:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 5:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 6:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
      case 7:
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;
      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        break;
    }
    SetDirection();
  }
}

void SetDirection() {
  if (Direction) { // if direction is true (clockwise)
    Steps++;
  } else { // if direction is false (counter-clockwise)
    Steps--;
  }
  if (Steps > 7) {
    Steps = 0;
  }
  if (Steps < 0) {
    Steps = 7;
  }
}