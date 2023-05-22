#include <Servo.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
int Steps = 0;
boolean Direction = true; // True: Clockwise, False: Counter-Clockwise
int stepsPerCommand = 4096; // Number of steps to take per command

Servo myservo;  // Create servo object
int pos = 0;    // Variable to store the servo position

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  myservo.attach(6); // Attaches the servo on pin 6
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
      pos = max(0, pos - 15); // Decrease servo position
      myservo.write(pos);
    } else if (command == '8') {
      pos = min(180, pos + 15); // Increase servo position
      myservo.write(pos);
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