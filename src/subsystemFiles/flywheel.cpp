#include "main.h"

// Flywheel TBH loop variables
double current_rpm = 0.0;
double target_rpm = 0.0;
double error = 0.0;
double prev_error = 0.0;
double output = 0.0;
double tbh = 0.0;
float gain = 0.0;

// Flywheel control functions
void setFlywheelMotor() {
    // R1 forward, R2 disabled
    // Spins at 10v if blooper disabled, 10.5v if blooper enabled
    if ( bloopin_time ) {
        flywheel = (127.0 / 12.0 * 10.5) * (controller1.getDigital(ControllerDigital::R1));
    }
    else {
        flywheel = (127.0 / 12.0 * 10.0) * (controller1.getDigital(ControllerDigital::R1));
    }
}

void flywheelTBHLoop() {
    // Get the current RPM of the flywheel
    current_rpm = flywheel.get_actual_velocity();
    
    // Calculate the error between the current RPM and the target RPM
    error = target_rpm - current_rpm;

    output += gain * error;

    if ( (error > 0 && prev_error < 0) || (error < 0 && prev_error > 0) ) {
        output = 0.5 * (output + tbh);
        tbh = output;
        prev_error = error;
    }

    // Set the flywheel motor speeds based on the output voltage
    pros::lcd::set_text(1, std::to_string(output));
    flywheel.move_velocity(output);
}
