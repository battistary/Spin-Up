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
    // Reset motor encoders and gyro rotation
    resetDriveEncoders();
    imu.tare_rotation();
    // Drive forward until units are reached
    while(avgDriveEncoderValue() < abs(units)) {
        // Gyro correction if bot veers off path
        // If correction is too much, multiply gyro degrees by 0.75 or 0.5
        setDrive(voltage * direction - (imu.get_rotation() * 10), voltage * direction + (imu.get_rotation() * 10));
        pros::delay(10);
    }
    // Brief brake
    setDrive(-10 * direction, -10 * direction);
    pros::delay(50); // Calibrate to weight of our bot. ># -> Heavier bot, 50 is fairly light
    // Set drive back to neutral
    setDrive(0, 0);
}

void rotate(int degrees, int voltage) {
    // Define a direction based on the units provided
    int direction = abs(degrees) / degrees;
    // Reset gyro rotation
    imu.tare_rotation();
    // Turn until units - 5 degrees are reached
    setDrive(voltage * direction, -voltage * direction);
    while (fabs(imu.get_rotation() < abs(degrees)) - 5) {
        pros::delay(10);
    }
    // Wait for robot to loose momentum before performing corrections
    pros::delay(100);
    // Correct for overshoot
    if (fabs(imu.get_rotation() > abs(degrees))) {
        setDrive(0.5 * -voltage * direction, 0.5 * voltage * direction);
        while (fabs(imu.get_rotation() > abs(degrees))) {
            pros::delay(10);
        }
    // Correct for undershoot
    } else if (fabs(imu.get_rotation() < abs(degrees))) {
        setDrive(0.5 * voltage * direction, 0.5 * -voltage * direction);
        while (fabs(imu.get_rotation() > abs(degrees))) {
            pros::delay(10);
        }
    }
    // Reset drive to zero
    setDrive(0, 0);
}
