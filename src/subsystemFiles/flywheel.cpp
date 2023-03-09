#include "main.h"

// Flywheel control functions
void setFlywheelMotor() {
    // R1 forward, R2 disabled
    flywheel = (127.0 / 12.0 * 9.1) * (controller1.getDigital(ControllerDigital::R1));
}
