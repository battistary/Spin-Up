#include "main.h"
#include "pros/misc.h"

bool launchStringLeft = false;
bool launchStringRight = false;

// String launcher control functions
void setStringLaunchers() {
  if ( controller2.getDigital(ControllerDigital::left) ) {
    if ( launchStringLeft == false ) {
      stringLauncher1.set_value(1);
      launchStringLeft = true;
      pros::delay(500);
    }
    else {
      stringLauncher1.set_value(0);
      launchStringLeft = false;
      pros::delay(500);
    }
  }
  if ( controller2.getDigital(ControllerDigital::right) ) {
    if ( launchStringRight == false ) {
      stringLauncher2.set_value(1);
      launchStringRight = true;
      pros::delay(500);
    }
    else {
      stringLauncher2.set_value(0);
      launchStringRight = false;
      pros::delay(500);
    }
  }
}
