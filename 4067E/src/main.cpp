              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cheni & William                                           */
/*    Created:      Thu May 19 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>

using namespace vex;

//CHANGE THESE VALUES FOR PORTS

competition Competition;

controller Controller1; 

motor lFront (PORT6, ratio18_1, true); //LEFT FRONT MOTOR 
motor rFront (PORT9, ratio18_1); //RIGHT FRONT MOTOR 
motor lBack (PORT8, ratio18_1, true);  //LEFT BACK MOTOR
motor rBack (PORT7, ratio18_1);  //RIGHT BACK MOTOR

motor arm (PORT5, ratio18_1);

<<<<<<< Updated upstream
motor flywheelIntake (PORT1, ratio18_1);
motor flywheelShoot (PORT2, ratio36_1);

//motor_group flywheels (flywheel1, flywheel2);
=======
motor frontFlywheels (PORT1, ratio18_1); //INTAKE MOTOR
motor topFlyWheel(PORT5, ratio18_1); //SHOOTING FLY WHEEL MOTOR
motor rollerSpin (PORT12, ratio18_1); //MOTOR THAT SPINS ROLLER ON FIELD

>>>>>>> Stashed changes

motor_group lTrain (lBack, lFront); //LEFT DRIVETRAIN
motor_group rTrain (rBack, rFront); //RIGHT DRIVETRAIN



drivetrain Train (lTrain, rTrain); 



color teamColor = blue;  //if we are in blue team set this to true and redTeam = false 

float frontSpeed = 1  ;
float backSpeed = 1;
float driveSpeed = 1;
float armSpeed = 70;
float chainSpeed = 80;
float deflectorSpeed = 50;

float spinSpeed = 100; 

//flywheel variables


float flywheelSpeed = 75; 

//penumatics
bool ShooterBool = false;

//reverseDrive
bool reverseDrive = false; 

//turnpid
double turnKp = 1; 


//pid
double kP = 0.2; 
double kI = 0.; 
double kD = 0.0;

float wheelCircumferenceIch = 12.566370;

int driveDistance(float targetDistance) {
  float integral = 0;
  float prevError = 0; 
  float prevTime = 0; 
  lTrain.resetPosition();
  rTrain.resetPosition();
  float targetDeg = targetDistance / wheelCircumferenceIch * 360; 
  while (1) {

    int lTrainPosition = lTrain.position(degrees);
    int rTrainPosition = rTrain.position(degrees);

    int averageMotorGroupPosition = (lTrainPosition + rTrainPosition) / 2;
    // Propotional
    float error = targetDeg - averageMotorGroupPosition;
    

    float deltaTime = (vex::timer::system() - prevTime); 
    prevTime= vex::timer::system();
    integral += prevError * deltaTime;
    
    int motorPower = (error * kP + integral * kI);

    lTrain.spin(forward, motorPower * driveSpeed, pct);
    rTrain.spin(forward, motorPower * driveSpeed, pct);

    std::cout << error ;
     

    prevError = error; 
    
    wait(20, msec);

  }
  return 1;
}

void turnLeft() { 
  lTrain.spinFor(reverse, 90, degrees);
  rTrain.spinFor(fwd, 90, degrees);
}

/*
void aimBot() { 
  while(1){
    Vision20.takeSnapshot(Vision20__SIG_1);
    if (Vision20.largestObject.centerX < 138) { 
      rTrain.spin(reverse, 30, pct);
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 0);
      Controller1.Screen.print("movingleft");
      Vision20.takeSnapshot(Vision20__SIG_1);
    }
    
    else if (Vision20.largestObject.centerX > 178){
      lTrain.spin(fwd, 30, pct);
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(2, 2);
      Controller1.Screen.print("movingRight");
      Vision20.takeSnapshot(Vision20__SIG_1);
    } 
    else if(Vision20.largestObject.centerX < 138 && Vision20.largestObject.centerX > 178) { 
      lTrain.spin(forward, 30, pct); 
      rTrain.spin(forward, 30, pct);
    }
    else { 
      lTrain.stop();
      rTrain.stop();
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(3, 2);
      Controller1.Screen.print("Straight");
      Vision20.takeSnapshot(Vision20__SIG_1);
      Vision20.takeSnapshot(Vision20__SIG_1);
    }
  }


}
*/

void toggleFlywheel(){ 

}

void goForward(int deg) { 
  lTrain.spin(fwd, deg, percent);
  rTrain.spin(fwd, deg, percent);
}
//Toggle Reverse Drive 
void reversed() { 
  reverseDrive = !reverseDrive; 
}

//Switch Team Color
void switchTeam(){
  if(teamColor == blue) { 
    teamColor = red; 
    
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Team Color: ");
    Controller1.Screen.print("Blue");
  }
  else  {
    teamColor = blue; 
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Team Color: ");
    Controller1.Screen.print("Red ");
  }
  
  
}



//Auto Spin roller with optical sensor


void UpdateScreen() {
  if (Competition.isDriverControl()) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("User Control Active");
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Battery: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    
    
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("left Front: PORT");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("left Front: PORT");
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("left Front: PORT");
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("left Front: PORT");
  }
}

void turn() { 
  lTrain.spinFor(double rotation, rotationUnits units, double velocity, velocityUnits units_v)
  lTrain.spinFor(double time, timeUnits units, double velocity, velocityUnits units_v)
  lTrain.spinFor(fwd, 380, degrees);
  rTrain.spinFor(reverse, 380, degrees, 80, velocityUnits::);
}

void auton() { 
  turn();
  

  

}

void usercontrol(void) {
  // User control code here, inside the loop
  
  while (1) {
    Brain.Screen.setCursor(1, 1);

    
    //drive commands
    if (reverseDrive == false) { 
      lTrain.spin(vex::directionType::rev, Controller1.Axis3.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
      rTrain.spin(vex::directionType::rev, Controller1.Axis2.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
    }
    else { 
      lTrain.spin(vex::directionType::fwd, Controller1.Axis2.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
      rTrain.spin(vex::directionType::fwd, Controller1.Axis3.position(vex::percentUnits::pct) * driveSpeed, vex::velocityUnits::pct);
    }

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

<<<<<<< Updated upstream
    /*if (Controller1.ButtonY.pressing()) {
      actualFlywheel1.spin(fwd,spinSpeed, pct); 
      actualFlywheel2.spin(fwd,spinSpeed, pct);
      armToggle();
    }
    else {
      actualFlywheel1.spin(fwd,0,pct);
      actualFlywheel2.spin(fwd,0,pct);
    } */

    //intake code
    if (Controller1.ButtonL2.pressing()){
      flywheelIntake.spin(fwd, spinSpeed, pct);
    } else if (Controller1.ButtonL1.pressing()) {
      flywheelIntake.spin(fwd, -spinSpeed, pct);
    } else{
      flywheelIntake.spin(fwd, 0, pct);
    } 

    //shoot code
    if (Controller1.ButtonR2.pressing()){
      flywheelShoot.spin(fwd, spinSpeed, pct);
    } else if (Controller1.ButtonR1.pressing()) {
      flywheelShoot.spin(fwd, -spinSpeed, pct);
    } else{
      flywheelShoot.spin(fwd, 0, pct);
=======
    
    if(Controller1.ButtonR1.pressing()) { 
      frontFlywheels.spin(reverse, 100, pct); 
    }
    else if(Controller1.ButtonR2.pressing()){
      frontFlywheels.spin(fwd, 100, pct);
    }
    else if (Controller1.ButtonB.pressing()) {
      frontFlywheels.spin(fwd, 50, pct);
    }
    else { 
      frontFlywheels.stop(coast);
    }

    
    if(Controller1.ButtonL1.pressing()) { 
      topFlyWheel.spin(reverse, flywheelSpeed, pct); 
    }
    else if (Controller1.ButtonUp.pressing()) {
      topFlyWheel.spin(fwd, flywheelSpeed, pct); 
    }
    else { 
      topFlyWheel.stop(coast);
    }

    //Color Switcher
    if(Controller1.ButtonL2.pressing()){
      if (teamColor == blue) {
        if (Optical1.color() == red) {
          frontFlywheels.spin(fwd, 80, pct);
        } 
        else {
          frontFlywheels.stop(brake);
        }
      } 
      else {
        if (Optical1.color() == blue) {
          frontFlywheels.spin(fwd, 80, pct);
        } 
        else {
          frontFlywheels.stop(brake);
        }
      } 
    } 
    else {
      // REMOVE THIS IF ROBOT NOT WOKRING
    }

   

    if (Controller1.ButtonX.pressing()) {
      rearShooter1.set(true);
      wait(100, msec);
      rearShooter1.set(false);
      wait(500, msec); 
    
    }
    else {
       
      rearShooter1.set(false);
>>>>>>> Stashed changes
    }

    


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Controller1.ButtonLeft.pressed(switchTeam);
  Controller1.ButtonRight.pressed(reversed);
  vexcodeInit();
  Competition.autonomous(auton);
  Competition.drivercontrol(usercontrol); 
}
  