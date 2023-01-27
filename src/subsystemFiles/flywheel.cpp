#include "main.h"
#include "okapi/impl/device/controllerUtil.hpp"
#include "pros/misc.h"

// Helper functions
void setFlywheel(int power) {
    flywheel = power ;
}

// Flywheel control functions
void setFlywheelMotor() {
    //R1 fwd, R2 disabled
    int flywheelPower = 0;
    if (controller1.getDigital(ControllerDigital::R1)) {
        flywheelPower = 127;
    } else {
        flywheelPower = 0;
    }
    setFlywheel(flywheelPower);
}
