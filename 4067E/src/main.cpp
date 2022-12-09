// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision6              vision        6               
// ---- END VEXCODE CONFIGURED DEVICES ----
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

//CHANGE THESE VALUES FOR PORTS

competition Competition;

controller Controller1; 



motor lFront (PORT6, ratio18_1);
motor rFront (PORT9, ratio18_1); 
motor lBack (PORT8, ratio18_1);
motor rBack (PORT7, ratio18_1); 

motor arm (PORT5, ratio18_1);

motor flywheel1 (PORT1, ratio18_1);
motor flywheel2 (PORT2, ratio18_1);

motor_group flywheels (flywheel1, flywheel2);

motor actualFlywheel1(PORT5, ratio36_1); 
motor actualFlywheel2(PORT4, ratio36_1);

motor_group lTrain (lBack, lFront); 
motor_group rTrain (rBack, rFront); 

drivetrain Train (lTrain, rTrain); 

float frontSpeed = 1  ;
float backSpeed = 1;
float driveSpeed = 1;
float armSpeed = 70;
float chainSpeed = 80;
float deflectorSpeed = 50;

float spinSpeed = 100; 

float flywheelSpeed = 100; 

//pid
double kP = 0.0; 
double kI = 0.0; 
double kD = 0.0;

int desiredValue = 200; 

int error; //value - desiredValue (how much more degrees to go)
int prevError; //error 20ms ago
int derivative; //difference between error - prevError : speed
int totalError; 

double turnkP = 0.0; 
double turnkI = 0.0; 
double turnkD = 0.0; 

int turnError; //value - desiredValue (how much more degrees to go)
int turnPrevError; //error 20ms ago
int turnDerivative; //difference between error - prevError : speed
int turnTotalError; 


bool enablePID = true; 

/*
int drivePID() { 
  while(enablePID) { 
    lTrain.resetPosition(); 
    rTrain.resetPosition(); 

    int lTrainPosition = lTrain.position(degrees);
    int rTrainPosition = rTrain.position(degrees);
    
    //Lateral
    
    int averageMotorGroupPosition = (lTrainPosition + rTrainPosition)/2;
    //Propotional
    error = desiredValue - averageMotorGroupPosition; 
    //Derivative
    derivative = error - prevError; 
    //Integral
    totalError += error; 

    

    int motorPower = (error * kP + derivative * kD + totalError * kI);
    
    //Turning
   

    int averageMotorGroupPosition = (lTrainPosition + rTrainPosition)/2;
    //Propotional
    turnError = desiredValue - averageMotorGroupPosition; 
    //Derivative
    turnDerivative = error - prevError; 
    //Integral
    turnTotalError += error; 

    

    int motorPower = (error * kP + derivative * kD + totalError * kI);


    
    lTrain.spin(fwd, motorPower * driveSpeed, pct);
    rTrain.spin(reverse, motorPower * driveSpeed, pct);

    prevError  = error; 
    wait(20, msec); 
  }

  return 1; 
}
*/




void aimBot(bool on) { 
  
  //Vision6.takeSnapshot(Vision6__SIG_1);
 

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

void autonomous1() { 
  //drivePID(); 


}

void UpdateScreen(){ 
  if (Competition.isDriverControl()) 
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("User Control Active");
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(lFront.power());
      //Controller1.Screen.setCursor(2, 3);
      //Controller1.Screen.print(lFront.current(amp));
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print("actualFlywheel = 6");
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("Battery: ");
      Controller1.Screen.print(Brain.Battery.capacity());
      Controller1.Screen.print("%%");
  }

  
  
  
}


void usercontrol(void) {
  // User control code here, inside the loop
  enablePID = false;
  while (1) {
    Brain.Screen.setCursor(1, 1); 
    Brain.Screen.print(actualFlywheel1.temperature());

    //drive commands
    lTrain.spin(vex::directionType::fwd, Controller1.Axis3.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
    rTrain.spin(vex::directionType::rev, Controller1.Axis2.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);

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

    

    if (Controller1.ButtonY.pressing()) {
      actualFlywheel1.spin(fwd,spinSpeed, pct); 
      actualFlywheel2.spin(fwd,spinSpeed, pct);
      armToggle();
    }
    else {
      actualFlywheel1.spin(fwd,0,pct);
      actualFlywheel2.spin(fwd,0,pct);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
    
    
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous1);
  Competition.drivercontrol(usercontrol); 
}
  