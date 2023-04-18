#include "main.h"
#include "pros/misc.h"

bool bloopin_time = false;

// Blooper control functions
void setBlooper() {
  if (controller1.getDigital(ControllerDigital::A)) { // Set to controller2 for comp
    if ( bloopin_time == false ) {
      blooper.set_value(1);
      bloopin_time = true;
      pros::delay(500);
    }
    else {
      blooper.set_value(0);
      bloopin_time = false;
      pros::delay(500);
    }
  }
}
