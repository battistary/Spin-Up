/*
    Not in use because lack of quadrature encoders casuses innaccurate turn PID
*/

//#include "main.h"
//
///**
// * Runs the user autonomous code. This function will be started in its own task
// * with the default priority and stack size whenever the robot is enabled via
// * the Field Management System or the VEX Competition Switch in the autonomous
// * mode. Alternatively, this function may be called in initialize or opcontrol
// * for non-competition testing purposes.
// *
// * If the robot is disabled or communications is lost, the autonomous task
// * will be stopped. Re-enabling the robot will restart the task, not re-start it
// * from where it left off.
// */
//void autonomous() {
//  
//    /**************************************
//    *             Skills auton            *
//    **************************************/
//
//    else if (selector::auton == 0) {
//        // Assumes robot is 13" wide and 17.5" long
//        // Set the odometric starting position (front-middle align)
//        // Notation: {Forward, Right};
//        chassis->setState({2_in, 29.5_in, 0_deg});
//        intakeController->tarePosition();
//
//        // Drive backwards and spin roller
//        chassis->driveToPoint({0_in, 29.5_in}, true); // adjust for roller 0 -> 1.5
//        chassis->waitUntilSettled();
//        intakeController->setTarget(-1200);
//        intakeController->waitUntilSettled();
//        intakeController->tarePosition();
//
//        // Drive to next roller, get disc, and spin
//        chassis->driveToPoint({3.25_in, 29.5_in});
//        intake.move(127);
//        chassis->driveToPoint({27.25_in, 5.5_in});
//        chassis->waitUntilSettled();
//        intake.brake();
//        chassis->driveToPoint({27.25_in, 1.5_in}, true); // adjust for roller 0 -> 1.5
//        chassis->waitUntilSettled();
//        intakeController->setTarget(330);
//        intakeController->waitUntilSettled();
//        intakeController->tarePosition();
//
//        // Drive to goal and shoot 3 discs
//        chassis->driveToPoint({27.25_in, 5.5_in});
//        chassis->driveToPoint({78.5_in, 5.5_in});
//        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
//        chassis->waitUntilSettled();
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        flywheel.brake();
//
//        // Drive back, intake 3 discs, and shoot
//        chassis->driveToPoint({27.25_in, 5.5_in}, true);
//        intake.move(127);
//        chassis->driveToPoint({75.25_in, 53.5_in});
//        chassis->waitUntilSettled();
//        intake.brake();
//        chassis->driveToPoint({123.25_in, 53.5_in});
//        chassis->driveToPoint({123.25_in, 56.75_in});
//        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
//        chassis->waitUntilSettled();
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        flywheel.brake();
//
//        // Intake 3 more discs and shoot
//        chassis->driveToPoint({123.25_in, 53.5_in}, true);
//        intake.move(127);
//        chassis->driveToPoint({51.25_in, 125.5_in});
//        chassis->waitUntilSettled();
//        intake.brake();
//        chassis->driveToPoint({54.5_in, 125.5_in});
//        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
//        chassis->waitUntilSettled();
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        flywheel.brake();
//
//        // Intake 3 more discs, spin 2 rollers, fire 3 discs, shoot string from corner
//        chassis->driveToPoint({51.25_in, 125.5_in}, true);
//        chassis->driveToPoint({87.25_in, 89.5_in}, true);
//        intake.move(127);
//        chassis->driveToPoint({128.75_in, 126.5_in});
//        chassis->waitUntilSettled();
//        intake.brake();
//        chassis->driveToPoint({104.5_in, 102.5_in}, true);
//        chassis->driveToPoint({104.5_in, 125_in}, true); // adjust for roller 126.5 -> 125
//        chassis->waitUntilSettled();
//        intakeController->setTarget(330);
//        intakeController->waitUntilSettled();
//        intakeController->tarePosition();
//        chassis->driveToPoint({104.5_in, 102.5_in});
//        chassis->driveToPoint({125_in, 102.5_in}, true); // adjust for roller 126.5 -> 125
//        chassis->waitUntilSettled();
//        intakeController->setTarget(330);
//        intakeController->waitUntilSettled();
//        intakeController->tarePosition();
//        chassis->driveToPoint({123.25_in, 102.5_in});
//        chassis->driveToPoint({123.25_in, 65.5_in});
//        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
//        chassis->waitUntilSettled();
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        intakeController->setTarget(-180);
//        intakeController->tarePosition();
//        pros::delay(1000);
//        flywheel.brake();
//        chassis->driveToPoint({128.75_in, 126.5_in}, true);
//        chassis->turnToAngle(-135_deg);
//        stringLauncher1.set_value(1);
//        stringLauncher2.set_value(1);
//    }
//}
