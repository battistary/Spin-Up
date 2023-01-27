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

// Autonomous Driving Functions
void translate(int units, int voltage) {
    // Define a direction based on units provided
    int direction = abs(units) / units; // Returns either 1 or -1

    resetDriveEncoders();

    // Drive forward until units are reached
    
}
