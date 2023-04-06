#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

// String launcher control functions
void setBlooper() {
  if (controller2.getDigital(ControllerDigital::up)) {
    blooper.set_value(1);
    // change flywheel voltage to 10.5v from 10v
    bloopin_time = true;
    pros::delay(500);
  }

  if (controller2.getDigital(ControllerDigital::down)) {
    blooper.set_value(0);
    // change flywheel voltage to 10v from 10.5v
    bloopin_time = false;
    pros::delay(500);
  }
}
