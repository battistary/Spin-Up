#include "main.h"

// Helper functions
void setIntake(int power) {
    intake = power;
}

// Intake control functions
void setIntakeMotor() {
    //L2 fwd, L1 rev
    int intakePower = 127 * (controller1.getDigital(ControllerDigital::L2) - controller1.getDigital(ControllerDigital::L1));
    setIntake(intakePower);
}
