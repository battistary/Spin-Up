#include "main.h"

// Flywheel control functions
void setFlywheelMotor() {
    // R1 forward, R2 disabled
    // Spins at 10v if blooper disabled, 10.5v if blooper enabled
    if ( bloopin_time ) {
        flywheel = (127.0 / 12.0 * 10.0) * (controller1.getDigital(ControllerDigital::R1));
    }
    else {
        flywheel = (127.0 / 12.0 * 9.25) * (controller1.getDigital(ControllerDigital::R1));
    }
}
