#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT1, ratio18_1, true);
motor rightMotor = motor(PORT10, ratio18_1, false);
line LineTrackerLeft = line(Brain.ThreeWirePort.C);
line LineTrackerRight = line(Brain.ThreeWirePort.D);
sonar RangeFinderA = sonar(Brain.ThreeWirePort.A);
inertial inert = inertial(PORT3);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}