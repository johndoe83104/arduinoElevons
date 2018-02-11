#include <Servo.h>

#define RANGE 120

Servo left;
Servo right;

word sensorValue1 = 0;    // lift row value
word sensorValue2 = 0;    // roll raw value
byte lift = 0;       
byte reverseLift = 0;
byte roll = 0;        
byte leftServo = 0;
byte rightServo = 0;
byte rollLeft = 0;
byte rollRight = 0;

void setup() {
  left.attach(9);
  right.attach(10);
  //Serial.begin(9600);
}

void loop() {

  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);

  lift = map(sensorValue1, 108, 925, 50, RANGE);
  roll = map(sensorValue2, 164, 934, 0, 70);
  reverseLift = map(sensorValue1, 108, 925, RANGE, 50);

  rollLeft = constrain(roll, 35, 70);
  rollLeft = map(rollLeft, 35, 70, 0, 35);
  rollRight = constrain(roll, 0, 35);
  rollRight = map(rollRight, 0, 35, 35, 0);

  leftServo = constrain((lift-rollLeft+rollRight), 50, RANGE);
  rightServo = constrain((reverseLift+rollRight-rollLeft), 50, RANGE);
  left.write(leftServo);
  right.write(rightServo);    

  //Serial.print("sensor = ");
  //Serial.print(sensorValue2);
  //Serial.print("\t output = ");
  //Serial.println(rollLeft);
}
