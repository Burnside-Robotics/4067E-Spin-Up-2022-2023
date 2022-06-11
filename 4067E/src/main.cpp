/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\cheni                                            */
/*    Created:      Thu May 19 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

controller Controller1; 

motor lFront (PORT10, ratio18_1);
motor rFront (PORT9, ratio18_1); 
motor lBack (PORT8, ratio18_1);
motor rBack (PORT7, ratio18_1); 

motor arm (PORT5, ratio18_1);

motor flywheel (PORT1, ratio18_1);

motor_group lTrain (lBack, lFront); 
motor_group rTrain (rBack, rFront); 

drivetrain Train (lTrain, rTrain); 

float frontSpeed = 1  ;
float backSpeed = 1;
float driveSpeed = 1;
float armSpeed = 70;
float chainSpeed = 80;
float deflectorSpeed = 50;

float flywheelSpeed = 100; 



double kP = 0.25;
double kI = 0.0;
double kD = 0.1;

double turnkP = 0.2; 
double turnkI = 0.0;
double turnkD = 0.1;

//autonomous settings
int desiredValue = 20;
int desiredTurnValue = 0;

int error;//sensorvalue - desiredvalue : position
int prevError = 0; //postion 20 msec ago
int derivative;//error - preverror : speed
int totalError;

int turnError;//sensorvalue - desiredvalue : position
int turnPrevError = 0; //postion 20 msec ago
int turnDerivative;//error - preverror : speed
int turnTotalError;

const float WHEEL_CIRCUMFERENCE = 31.9185812596;
const float MOTOR_ACCEL_LIMIT = 8;

int s_lastL = 0;
int s_lastR = 0; 

void DriveDistance(int dist, float maxTime)
{
  lBack.resetPosition();
  rBack.resetPosition();
  lFront.resetPosition();
  rFront.resetPosition();

  //Constant Tuning Values
  const float Kp = 1;
  const float Kd = 0;
  const float Ki = 0;

  float rotationGoal = (dist / WHEEL_CIRCUMFERENCE) * 360;




  float distError = 0;
  float integral = 0;
  float derivative = 0;
  float lastError = 0;

  float motorSpeed = 0;
  
  float doneTime = 0;
  while(maxTime > doneTime / 1000)
  {
    distError = rotationGoal - lFront.rotation(deg);

    integral += distError;

    if(distError > 200 || distError < -200)
    {
      integral  = 0;
    }

    derivative = distError - lastError;

    lastError = distError;

    motorSpeed = Kp * distError + Ki * integral + Kd * derivative;
    lTrain.spin(forward, motorSpeed, pct);
    rTrain.spin(forward, motorSpeed, pct);
  }
}


void armToggle() {
  static bool armToggle1 = false; 

  armToggle1 = !armToggle1; 
  if (armToggle1 == true) { 
    arm.spinFor(90, degrees); 
  }
  else { 
    arm.spinFor(-90, degrees); 
  }
  
  
}

void autonomous() { 
 DriveDistance(15, 10);
}

void UpdateScreen() {
  Controller1.Screen.clearScreen();

  if (Competition.isDriverControl()) 
  {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("User Control Active");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Battery: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    Controller1.Screen.print("%%");
  }
  else if (Competition.isAutonomous()) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Autonomous");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Battery: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    Controller1.Screen.print("%%");
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    //drive commands
    lTrain.spin(vex::directionType::fwd, Controller1.Axis3.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
    rTrain.spin(vex::directionType::fwd, Controller1.Axis2.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);

    //Stops the motor if the controller joystick's position is equal to 0
    if(Controller1.Axis2.position() == 0){
      rTrain.stop(vex::brake);
    }
    else if(Controller1.Axis3.position() == 0){
      lTrain.stop(vex::brake);
    }
    else if(Controller1.Axis2.position() == 0 && Controller1.Axis3.position() == 0){
      rTrain.stop(vex::brake);
      lTrain.stop(vex::brake);
    }

    if(Controller1.ButtonA.pressing()){
      flywheel.spin(fwd, flywheelSpeed, pct);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
    Controller1.ButtonB.pressed(armToggle); 
    
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  UpdateScreen(); 
  Competition.drivercontrol(usercontrol); 

}
