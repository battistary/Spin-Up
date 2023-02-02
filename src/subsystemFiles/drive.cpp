#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"

// Helper functions
void setDrive(int left, int right) {
    driveLeft = left;
    driveRight = right;
}

void resetDriveEncoders() {
    driveLeftFront.tare_position();
    driveLeftCenter.tare_position();
    driveLeftBack.tare_position();
    driveRightFront.tare_position();
    driveRightCenter.tare_position();
    driveRightBack.tare_position();
}

double avgDriveEncoderValue() {
    return (fabs(driveLeftFront.get_position()) +
    fabs(driveLeftCenter.get_position()) +
    fabs(driveLeftBack.get_position()) +
    fabs(driveRightFront.get_position()) +
    fabs(driveRightCenter.get_position()) +
    fabs(driveRightBack.get_position())) / 6;
}

// Autonomous Driving Functions
void translate(int units, int voltage) {
    // Define a direction based on units provided
    int direction = abs(units) / units; // Returns either 1 or -1
    // Reset motor encoders
    resetDriveEncoders();
    // Drive forward until units are reached
    while(avgDriveEncoderValue() < abs(units)) {
        setDrive(voltage * direction, voltage * direction);
        pros::delay(10);
    }
    // Brief brake
    setDrive(-10 * direction, -10 * direction);
    pros::delay(50); // Calibrate to weight of our bot. ># -> Heavier bot, 50 is fairly light
    // Set drive back to neutral
    setDrive(0, 0);
}
