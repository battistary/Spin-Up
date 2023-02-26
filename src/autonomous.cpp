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
        // Notation: {Forward, Right}
        chassis->setState({6.5_in, 29.5_in, 0_deg});

        // Drive backwards and spin roller
        chassis->driveToPoint({0_in, 29.5_in}, true); // adjust for roller
        chassis->waitUntilSettled();
        intakeController->setTarget(330);
        intakeController->waitUntilSettled();

        // Drive to next roller, get disc, and spin
        chassis->driveToPoint({3.25_in, 29.5_in});
        intake.move(127);
        chassis->driveToPoint({27.25_in, 5.5_in});
        chassis->waitUntilSettled();
        intake.brake();
        chassis->driveToPoint({27.25_in, 0_in}, true); // adjust for roller
        chassis->waitUntilSettled();
        intakeController->setTarget(330);
        intakeController->waitUntilSettled();

        // Drive to goal and shoot 3 discs
        chassis->driveToPoint({27.25_in, 5.5_in});
        chassis->driveToPoint({78.5_in, 5.5_in});
        flywheel.move(92);
        chassis->waitUntilSettled();
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        flywheel.brake();

        // Drive back, intake 3 discs, and shoot
        chassis->driveToPoint({27.25_in, 5.5_in}, true);
        intake.move(127);
        chassis->driveToPoint({75.25_in, 53.5_in});
        chassis->waitUntilSettled();
        intake.brake();
        chassis->driveToPoint({123.25_in, 53.5_in});
        chassis->driveToPoint({123.25_in, 65.5_in}, true);
        flywheel.move(92);
        chassis->waitUntilSettled();
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        flywheel.brake();

        // Intake 3 more discs and shoot
        chassis->driveToPoint({123.25_in, 53.5_in});
        intake.move(127);
        chassis->driveToPoint({51.25_in, 125.5_in});
        chassis->waitUntilSettled();
        intake.brake();
        chassis->driveToPoint({65.5_in, 125.5_in}, true);
        flywheel.move(92);
        chassis->waitUntilSettled();
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        flywheel.brake();

        // Intake 3 more discs, spin 2 rollers, fire 3 discs, shoot string from corner
        chassis->driveToPoint({51.25_in, 125.5_in});
        chassis->driveToPoint({87.25_in, 89.5_in}, true);
        intake.move(127);
        chassis->driveToPoint({128.75_in, 126.5_in});
        chassis->waitUntilSettled();
        intake.brake();
        chassis->driveToPoint({104.5_in, 102.5_in}, true);
        chassis->driveToPoint({104.5_in, 126.5_in}, true); // adjust for roller
        chassis->waitUntilSettled();
        intakeController->setTarget(330);
        intakeController->waitUntilSettled();
        chassis->driveToPoint({104.5_in, 102.5_in});
        chassis->driveToPoint({126.5_in, 102.5_in}, true); // adjust for roller
        chassis->waitUntilSettled();
        intakeController->setTarget(330);
        intakeController->waitUntilSettled();
        chassis->driveToPoint({123.25_in, 102.5_in});
        chassis->driveToPoint({123.25_in, 65.5_in});
        flywheel.move(92);
        chassis->waitUntilSettled();
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        pros::delay(1000);
        intakeController.setTarget(-180);
        flywheel.brake();
        chassis->driveToPoint({128.75_in, 126.5_in}, true);
        chassis->turnToAngle(-135_deg);
        stringLauncher1.set_value(1);
        stringLauncher2.set_value(1);
    }
}
