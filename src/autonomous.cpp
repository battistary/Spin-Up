#include "main.h"
#include "okapi/api/chassis/controller/chassisController.hpp"
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
        // Assumes robot is 13" wide and 17.5" long
        // Jig (back-middle) tile align
        // Tare intake motor starting position
        pros::lcd::initialize();
        static Gif gif("/usd/logo_stretched.gif", lv_scr_act());
        intakeController->tarePosition();
        
        chassis->moveDistance(-2.5_in); // Jig-roller distance
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
    }   

    /**************************************
    *        Right side match auton       *
    **************************************/

    else if (selector::auton == 2 || selector::auton == -2) {
        // Assumes robot is 13" wide and 17.5" long
        // Front-middle tile align
        // Tare intake motor starting position
        pros::lcd::initialize();
        static Gif gif("/usd/logo_stretched.gif", lv_scr_act());
        intakeController->tarePosition();

        // Drive forward, intake third disc, turn, and shoot
        intake.move(-127);
        flywheel.move(127.0 / 12.0 * 11.7); // 9.2v scaled out of 127
        chassis->moveDistance(20.75_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(23, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(8_in);
        chassis->waitUntilSettled();
        intake.tare_position();
        intakeController->setTarget(300);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(300);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(300);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(200);
        flywheel.brake();
        chassis->moveDistance(-8_in);
        chassis->waitUntilSettled();

        // Intake 2 more discs, shoot
        /*rotate(-45, 38);
        chassis->waitUntilSettled();
        intake.move(-127);
        flywheel.move(127.0 / 12.0 * 12); // 9.2v scaled out of 127
        chassis->moveDistance(33.94112549695428_in);
        chassis->waitUntilSettled();
        pros::delay(1000);
        intake.brake();
        rotate(45, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(12_in);
        intake.tare_position();
        intakeController->setTarget(100);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(200);
        intakeController->setTarget(100);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(200);
        flywheel.brake();
        chassis->moveDistance(-12_in);
        chassis->waitUntilSettled();*/

        // Turn, drive back to roller, spin roller
        rotate(-45, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-32_in);
        chassis->waitUntilSettled();
        rotate(0, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-5.5_in);
        chassis->waitUntilSettled();
        intake.tare_position();
        intakeController->setTarget(-800);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
    }

    /**************************************
    *             Skills auton            *
    **************************************/

    else if (selector::auton == 0){
        // Assumes robot is 13" wide and 17.5" long
        // Tare intake motor starting position
        // 130 points
        pros::lcd::initialize();
	    static Gif gif("/usd/logo_stretched.gif", lv_scr_act());
        chassis->setMaxVelocity(600);
        intakeController->tarePosition();

        // Drive backwards 2" and spin roller
        chassis->moveDistance(-2.5_in); // adjusted for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Drive to next roller, get disc, and spin
        chassis->moveDistance(5_in); // 7.75" to clear roller
        chassis->waitUntilSettled();
        rotate(-45, 38);
        intake.move(-127);
        chassis->waitUntilSettled();
        chassis->moveDistance(33.94112549695428_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(90, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-4.5_in); // adjusted for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Drive to goal and shoot 3 discs
        flywheel.move(127.0 / 12.0 * 9.2); // 9.2v scaled out of 127
        chassis->moveDistance(8_in);
        chassis->waitUntilSettled();
        rotate(0, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(51.25_in);
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(800);
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(800);
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Drive back, intake 3 discs, and shoot
        chassis->moveDistance(-51.25_in);
        intake.move(-127);
        chassis->waitUntilSettled();
        rotate(45, 38);
        chassis->waitUntilSettled();
        chassis->setMaxVelocity(400);
        chassis->moveDistance(72.88225099390856_in); // +5 to clear discs
        chassis->setMaxVelocity(600);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(0, 38);
        chassis->waitUntilSettled();
        flywheel.move(127.0 / 12.0 * 9.2); // 9.2v scaled out of 127
        chassis->moveDistance(40_in); // - 3.5355
        chassis->waitUntilSettled();
        rotate(-90, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(6.7855_in); // change
        chassis->waitUntilSettled();
        rotate(-102, 38);
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(800);
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(800);
        intakeController->setTarget(420);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Move to and spin next roller
        rotate(-90, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-3.25_in);
        chassis->waitUntilSettled();
        rotate(-45, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-16.97056274847714_in);
        chassis->waitUntilSettled();
        rotate(-90, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-36_in);
        chassis->waitUntilSettled();
        rotate(-180, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-13.3_in);
        chassis->waitUntilSettled();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Move to and spin last roller
        chassis->moveDistance(5_in);
        chassis->waitUntilSettled();
        rotate(-225, 38);
        intake.move(-127);
        chassis->waitUntilSettled();
        chassis->moveDistance(20_in);
        intake.brake();
        chassis->waitUntilSettled();
        rotate(-90, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-16_in); // adjusted for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();

        // Drive to corner and launch string
        chassis->moveDistance(16_in);
        chassis->waitUntilSettled();
        rotate(-135, 38);
        chassis->waitUntilSettled();
        chassis->moveDistance(-14_in);
        chassis->waitUntilSettled();
        stringLauncher1.set_value(1);
        stringLauncher2.set_value(1);
        pros::delay(500);
        chassis->moveDistance(8_in);
        


        /*chassis->moveDistance(101.8233764908628_in);
        chassis->waitUntilSettled();
        intake.brake();
        rotate(-180, 38);
        chassis->moveDistance(3.25_in);
        flywheel.move(127.0 / 12.0 * 9.2); // 9.2v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();

        // Intake 3 more discs, spin 2 rollers, fire 3 discs, shoot string from corner
        chassis->moveDistance(-3.25_in);
        rotate(-225, 38);
        chassis->moveDistance(-2.121320343559643_in);
        intake.move(-127);
        rotate(-315, 38);
        chassis->moveDistance(2.121320343559643_in);
        chassis->waitUntilSettled();
        intake.brake();
        chassis->moveDistance(-1.414213562373095_in);
        rotate(90, 38);
        chassis->moveDistance(-25.75_in); // adjust for roller 0 -> 1.5
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        chassis->moveDistance(25.75_in);
        rotate(0, 38);
        chassis->moveDistance(-25.75_in); // adjust for roller 126.5 -> 125
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(-1200);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        chassis->moveDistance(1.75_in);
        rotate(90, 38);
        chassis->moveDistance(51.25_in);
        flywheel.move(127.0 / 12.0 * 9.2); // 9.2v scaled out of 127
        pros::delay(3000);
        chassis->waitUntilSettled();
        intakeController->tarePosition();
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        intakeController->setTarget(550);
        intakeController->waitUntilSettled();
        intakeController->tarePosition();
        pros::delay(500);
        flywheel.brake();
        chassis->moveDistance(-75.25_in);
        rotate(-135, 38);
        //stringLauncher1.set_value(1);
        //stringLauncher2.set_value(1);*/
    }
}
