#include "main.h"
#include "okapi/impl/device/controllerUtil.hpp"

// Flywheel TBH loop variables
float current_fw_rpm = 0.0;
double error = 0.0;
double prev_error = 0.0;
double tbh = 0.0;
float gain = 0.01; //0.01;

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

void flywheelTBHLoop() {
    // Get the current RPM of the flywheel
    current_fw_rpm = flywheel.get_actual_velocity();
    
    // Calculate the error between the current RPM and the target RPM
    error = target_fw_rpm - current_fw_rpm;

    fw_output += gain * error;

    if ( (error > 0 && prev_error < 0) || (error < 0 && prev_error > 0) ) {
        fw_output = 0.5 * (fw_output + tbh);
        tbh = fw_output;
        prev_error = error;
    }
    
    if ( controller1.getDigital(ControllerDigital::R1) ) {
        // Set the flywheel motor speeds based on the fw_output voltage
        flywheel.move_velocity(fw_output);
    }
    else {
        current_fw_rpm = flywheel.get_actual_velocity();
        fw_output = 0.0;
        tbh = 0.0;
        prev_error = 0.0;
        flywheel.brake();
    }
    pros::lcd::set_text(1, std::to_string(current_fw_rpm));
}

void resetFlywheelTBH() {
    if ( controller1.getDigital(ControllerDigital::Y) ) {
        flywheel.brake();
        double error = 0.0;
        double prev_error = 0.0;
        fw_output = 0.0;
        double tbh = 0.0;
    }
}
