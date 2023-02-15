#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision20__SIG_1 = signature (1, 3043, 10163, 6602, -1017, 765, -126, 1, 0);
vision Vision20 = vision (PORT20, 42, Vision20__SIG_1);
digital_out rearShooter1 = digital_out(Brain.ThreeWirePort.A);
digital_out expansion = digital_out(Brain.ThreeWirePort.B);
optical Optical1 = optical(PORT2);

/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}