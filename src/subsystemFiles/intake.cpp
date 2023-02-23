#include "main.h"

// Intake control functions
void setIntakeMotor() {
    // L2 forward, L1 reverse
    intake = 127 * (controller1.getDigital(ControllerDigital::L2) - controller1.getDigital(ControllerDigital::L1));
}
