/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\celinawhitmer                                    */
/*    Created:      Sat Mar 25 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         10              
// LineTrackerLeft      line          C               
// LineTrackerRight     line          D               
// RangeFinderA         sonar         A, B            
// inert                inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


const float wheelDiameter = 4.0;
const float wheelCircumference = 3.14 * wheelDiameter;
const float gearRatio = 5.0;
const float motorCountsPerRev = 900.0;
const float countsPerInch = motorCountsPerRev * gearRatio / wheelCircumference;
const float setMotorVoltage = 10;  // set motor effort
const float setMotorRev = 70;
const float Kp = 7.5;               // left-right count error proportionality constant
const float wheelTrack = 11; 
const float degreesPerInch = 360.0 / wheelCircumference;

void driveStraight(float motorVoltage, float distance) {   //provide a voltage (effort) from 0 to 12
  int distanceCount = (int)(countsPerInch*distance);       //use (int) to change a float to an int
  leftMotor.resetRotation();  //reset the encoder counts to zero
  rightMotor.resetRotation();
  printf("%f  \n", leftMotor.rotation(vex::rotationUnits::raw));  //print the current left motor encoder count
  while (leftMotor.rotation(vex::rotationUnits::raw) < distanceCount){
    float leftRightCountDiff = (leftMotor.rotation(vex::rotationUnits::raw) - rightMotor.rotation(vex::rotationUnits::raw));
    leftMotor.spin(forward, motorVoltage - Kp*leftRightCountDiff, volt);
    rightMotor.spin(forward, motorVoltage + Kp*leftRightCountDiff, volt);
    printf("%f  \n", leftMotor.velocity(rpm));
    wait(.01,seconds);
    //vexDelay(10);
  }
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}

void drive(float speed, float direction)
 {
   leftMotor.setVelocity(speed - direction, rpm);
   rightMotor.setVelocity(speed + direction, rpm);
   leftMotor.spin(fwd);
   rightMotor.spin(fwd);
 }
  void turn(float targetDegrees)   //Positive targetDegrees turns left.
{
  float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter; 
  leftMotor.spinFor(reverse, rotationDegrees, degrees, false);
  rightMotor.spinFor(forward, rotationDegrees, degrees, true);
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  inert.calibrate();
 wait(4, sec);

 inert.setHeading(0, degrees); //return heading to 0 

 float head = inert.heading(degrees); //gets heading (Z axis rotation)  //wraps the value between -180 and 180 degrees 
 if(head > 180){
 head = head - 360;
 
 double pitch = inert.pitch(degrees);
 }

  Brain.Screen.printAt(30, 30, "%f      \n", inert.heading(degrees));
  Brain.Screen.printAt(90, 90, "%f      \n", inert.heading(degrees));
  while(RangeFinderA.distance(inches) > 11) {
    Brain.Screen.printAt(120, 120, "%f      \n", head);
    head = inert.heading(degrees); //gets heading (Z axis rotation)  //wraps the value between -180 and 180 degrees 
    if(head > 180){
      head = head - 360;
    }
    float error = head;
    drive(setMotorRev, error * Kp);
    wait(0.01,sec);
  }

  printf("gg");
  turn(90);
  wait(0.01, sec);
  while(RangeFinderA.distance(inches) > 6) {
    Brain.Screen.printAt(120, 120, "%f      \n", inert.heading(degrees));
    head = inert.heading(degrees); //gets heading (Z axis rotation)  //wraps the value between -180 and 180 degrees 
    if(head > 180){
      head = head - 360;
    }
    float error = head - -105;
    drive(setMotorRev, error * Kp);
    wait(0.01,sec);
  }
  turn(90);
  wait(0.01, sec);
  while(RangeFinderA.distance(inches) > 5) {
    Brain.Screen.printAt(120, 120, "%f      \n", inert.heading(degrees));
    head = inert.heading(degrees); //gets heading (Z axis rotation)  //wraps the value between -180 and 180 degrees 
    if(head > 180){
      head = head - 360;
    }
    float error = head - 145;
    drive(setMotorRev, error * Kp);
    wait(0.01,sec);
  }
  
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}