#include "main.h"
#include "pros/misc.h"

bool launchString = true;

// String launcher control functions
void setStringLaunchers() {
  if (controller2.getDigital(ControllerDigital::A)) {
    if (launchString) {
      stringLauncher1.set_value(1);
      stringLauncher2.set_value(1);
      launchString = false;
      pros::delay(500);
    }
    else {
      stringLauncher1.set_value(0);
      stringLauncher2.set_value(0);
      launchString = true;
      pros::delay(500);
    }
  }
}
