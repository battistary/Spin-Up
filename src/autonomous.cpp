#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

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
        chassis->moveDistance(48_in);

    }
        /*
        // 90 degree gyro rotation test @ 50/127v
        rotate(90, 38);
        pros::lcd::initialize();
        while ( true ) {
            pros::lcd::set_text(2, std::to_string(imu.get_rotation()));
            pros::delay(500);
        }
        
        //go back, hit roller, turn, shoot two disks
        //chassis ->driveToPoint({-10_in, 0_in});
        //intakeController->setTarget(338);
        //intakeController->waitUntilSettled();
        //chassis->driveToPoint({0_in, 0_in});
        //chassis->turnToAngle(-30_deg);
    }
*/
    /**************************************
    *        Right side match auton       *
    **************************************/
/**
    else if (selector::auton == 2 || selector::auton == -2) {
        // Set the odometric starting position
        chassis->setState({0_in, 0_in, 0_deg});

        // Distance PD Test
        chassis->driveToPoint({48_in, 0_in});
    }
*/
    /**************************************
    *             Skills auton            *
    **************************************/

    else if (selector::auton == 0){
        // Assumes robot is 13" wide and 17.5" long
        // Tare intake motor starting position
        pros::lcd::initialize();
        intakeController->tarePosition();

        // Drive backwards 2" and spin roller
        chassis->moveDistance(-2.5_in); // adjusted for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Drive to next roller, get disc, and spin
        chassis->moveDistance(5_in); // 7.75" to clear roller
        rotate(-45, 38);
        intake.move(-127);
        chassis->moveDistance(33.94112549695428_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(90, 38);
        chassis->moveDistance(-4.5_in); // adjusted for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Drive to goal and shoot 3 discs
        chassis->moveDistance(3_in);
        rotate(0, 38);
        pros::lcd::set_text(3, std::to_string(imu.get_rotation()));
        chassis->moveDistance(51.25_in);
        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Drive back, intake 3 discs, and shoot
        chassis->moveDistance(-51.25_in);
        intake.move(127);
        rotate(45, 38);
        chassis->moveDistance(67.88225099390856_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(0, 38);
        chassis->moveDistance(48_in);
        rotate(-90, 38);
        chassis->moveDistance(3.25_in);
        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Intake 3 more discs and shoot
        chassis->moveDistance(-3.25_in);
        intake.move(127);
        rotate(-225, 38);
        chassis->moveDistance(101.8233764908628_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(-180, 38);
        chassis->moveDistance(3.25_in);
        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Intake 3 more discs, spin 2 rollers, fire 3 discs, shoot string from corner
        chassis->moveDistance(-3.25_in);
        rotate(-225, 38);
        chassis->moveDistance(-2.121320343559643_in);
        intake.move(127);
        rotate(-315, 38);
        chassis->moveDistance(2.121320343559643_in);
        chassis->waitUntilSettled();
        intake.brake();
        chassis->moveDistance(-1.414213562373095_in);
        rotate(90, 38);
        chassis->moveDistance(-25.75_in); // adjust for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        chassis->moveDistance(25.75_in);
        rotate(0, 38);
        chassis->moveDistance(-25.75_in); // adjust for roller 126.5 -> 125
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        chassis->moveDistance(1.75_in);
        rotate(90, 38);
        chassis->moveDistance(51.25_in);
        flywheel.move(127.0 / 12.0 * 9.3); // 9.3v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(-500);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();
        chassis->moveDistance(-75.25_in);
        rotate(-135, 38);
        stringLauncher1.set_value(1);
        stringLauncher2.set_value(1);
    }
}
