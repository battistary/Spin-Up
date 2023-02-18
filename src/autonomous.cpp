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

        // Turn PD
        chassis->turnToAngle(90_deg);
    }

    /**************************************
    *        Right side match auton       *
    **************************************/
    
    else if (selector::auton == 2 || selector::auton == -2) {
        // Set the odometric starting position
        chassis->setState({0_in, 0_in, 0_deg});

        // Distance PD
        chassis->driveToPoint({48_in, 0_in});
    }

    /**************************************
    *             Skills auton            *
    **************************************/

    else if (selector::auton == 0) {
        // Assumes robot is 13" wide and 17.5" long
        // Set the odometric starting position (front-middle align)
        chassis->setState({6_in, 29.5_in, 0_deg});

        chassis->driveToPoint({0_in, 29.5_in}, true);
        chassis->waitUntilSettled();
        intakeController->setTarget(330);
        intakeController->waitUntilSettled();

        chassis->driveToPoint({5.5_in, 29.5_in});
        intake.move(127);
        chassis->driveToPoint({29.5_in, 5.5_in});
        chassis->waitUntilSettled();
        intake.brake();
        chassis->driveToPoint({79_in, 5.5_in});
        chassis->waitUntilSettled();
        flywheel.move(92);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        flywheel.brake();

        // Drive Examples:
        // turn 45 degrees and drive approximately 1.4 ft
        //chassis->driveToPoint({1_ft, 1_ft});
        // turn approximately 45 degrees to end up at 90 degrees
        //chassis->turnToAngle(90_deg);
        // turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
        //chassis->turnToPoint({5_ft, 0_ft});

        // Intake Examples:
        // spin 330 degrees
        // intakeController->setTarget(330);
        // wait for movement to finish
        // intakeController->waitUntilSettled();

        // Flywheel Examples:
        // spin flywheel forward at max voltage (-127 to +127)
        // flywheel.move(127);
        // stop flywheel
        // flywheel.brake();
    }
}
