#include <AccelStepper.h>


#define stepperPin1  4     // IN1 on the ULN2003 driver
#define stepperPin2  5     // IN2 on the ULN2003 driver
#define stepperPin3  6     // IN3 on the ULN2003 driver
#define stepperPin4  7     // IN4 on the ULN2003 driver


#define MotorInterfaceType 8  // Define the AccelStepper interface type; 4 wire motor in half step mode

/* Adujust These
---------------------------*/
int delayTime = 1000;
int steps = 1400;
int stepperSpeed = 1000; // I would leave this where it is at
/*-------------------------
       Adjust These*/

bool on = false;

AccelStepper stepper = AccelStepper(MotorInterfaceType, stepperPin1, stepperPin3, stepperPin2, stepperPin4);

void setup() {
  Serial.begin(9600);

  stepper.setMaxSpeed(1000);
  stepper.setCurrentPosition(0);
}

void loop() {
if (Serial.available() > 0) {
  int state = Serial.read();

  if (state == 'A' || state == 'a') {
    on = true;
  }

  if (state == 'B' || state == 'b') {
    stepper.move(100); 

    stepper.setSpeed(stepperSpeed);
    while (stepper.currentPosition() != stepper.targetPosition()) {
     stepper.runSpeedToPosition();
    }
   }
    
  if (state == 'C' || state == 'c') {
    stepper.move(-100); 

    stepper.setSpeed(-stepperSpeed);
    while (stepper.currentPosition() != stepper.targetPosition()) {
      stepper.runSpeedToPosition();
    }
  }

  while (on == true) {
    click();
  }
}// Serial Avalible
}// Loop

void click() {

  delay(delayTime);

  stepper.move(steps); 

  stepper.setSpeed(stepperSpeed);
  while (stepper.currentPosition() != stepper.targetPosition()) {
    stepper.runSpeedToPosition();
  }
  stepper.move(-steps);

  stepper.setSpeed(-stepperSpeed);
  while  (stepper.currentPosition() != stepper.targetPosition()) {
    stepper.runSpeedToPosition();
  }
}// Click
