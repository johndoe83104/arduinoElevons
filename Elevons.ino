#include <Servo.h>

#define servoUpRange 120                     //
#define servoDownRange 50
#define servoMaxRange 70                     // Define maximum rage of motion for the servo, from 0 to 70 degrees
#define servoMidRange 35                     // Define the midpoint of motion 
#define servoMinRange 0                      // Define the midpoint of motion 

Servo left;                                  // Create object for left servo
Servo right;                                 // Create object for right servo

word sensorValue1 = 0;                       // Read raw value for up/down motion for elevons
word sensorValue2 = 0;                       // Read raw value for roll, left/right motion for elevons
byte lift = 0;       
byte reverseLift = 0;
byte roll = 0;        
byte leftServo = 0;
byte rightServo = 0;
byte rollLeft = 0;
byte rollRight = 0;

void setup() {
  left.attach(9);                           // Attach servo to PWM pin 9
  right.attach(6);                          // Attach servo to PWM pin 6
}

void loop() {

  sensorValue1 = analogRead(A0);            // Read raw value from pot
  sensorValue2 = analogRead(A1);            // reatd raw value from pot

  lift = map(sensorValue1, 108, 925, servoDownRange, servoUpRange);                         // Map raw values from pots to 50-120
  roll = map(sensorValue2, 164, 934, servoMinRange, servoMaxRange);                         // Map raw values from pots to 0-70
  reverseLift = map(sensorValue1, 108, 925, servoUpRange, servoDownRange);

  rollLeft = constrain(roll, servoMidRange, servoMaxRange);
  rollLeft = map(rollLeft, servoMidRange, servoMaxRange, servoMinRange, servoMidRange);
  rollRight = constrain(roll, servoMinRange, servoMidRange);
  rollRight = map(rollRight, servoMinRange, servoMidRange, servoMidRange, servoMinRange);

  leftServo = constrain((lift-rollLeft+rollRight), servoDownRange, servoUpRange);
  rightServo = constrain((reverseLift+rollRight-rollLeft), servoDownRange, servoUpRange);
  
  left.write(leftServo);
  right.write(rightServo);    

}
