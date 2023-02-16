#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    // Display gif image on brain screen
    static Gif gif("/usd/logo_unstretched.gif", lv_scr_act());

    /**************************************
    *        Left side match auton        *
    **************************************/

    if (selector::auton == 1 || selector::auton == -1) {
        // Set the odometric starting position
        chassis->setState({0_in, 0_in, 0_deg});

        // Step 1
        //chassis->driveToPoint({48_in, 0_in});
        //chassis->turnToAngle(90_deg);

        // Test out gyro turns
        rotate(90, 80);
    }

    /**************************************
    *        Right side match auton       *
    **************************************/
    
    else if (selector::auton == 2 || selector::auton == -2) {
        // Set the odometric starting position
        chassis->setState({0_in, 0_in, 0_deg});

        // Distance PID
        chassis->driveToPoint({48_in, 0_in});
        //chassis->turnToAngle(90_deg);
    }

    /**************************************
    *             Skills auton            *
    **************************************/

    else if (selector::auton == 0) {
        // Set the odometric starting position
        chassis->setState({16_in, 24_in, 0_deg});

        chassis->driveToPoint({0_in, 0_in});
        
        intake.move_relative(330, 127);
        while (!((intake.get_position() < 333) && (intake.get_position() > 297))) {
            pros::delay(2);
        }
        intake.brake();

        // Examples:
        // turn 45 degrees and drive approximately 1.4 ft
        //chassis->driveToPoint({1_ft, 1_ft});
        // turn approximately 45 degrees to end up at 90 degrees
        //chassis->turnToAngle(90_deg);
        // turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
        //chassis->turnToPoint({5_ft, 0_ft});
    }
}
