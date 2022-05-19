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

motor_group lTrain (lBack, lFront); 
motor_group rTrain (rBack, rFront); 

drivetrain Train (lTrain, rTrain); 

float frontSpeed = 1  ;
float backSpeed = 1;
float driveSpeed = 1;
float armSpeed = 70;
float chainSpeed = 80;
float deflectorSpeed = 50;

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

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  UpdateScreen(); 
  Competition.drivercontrol(usercontrol); 

}
