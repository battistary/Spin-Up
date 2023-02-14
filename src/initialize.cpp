#include "main.h"
#include "pros/llemu.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/screen.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// Drive motors
	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftCenter.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightCenter.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	// Motor groups
	driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	// Subsystem Motors
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	// Pneumatics
	stringLauncher1.set_value(0);
	stringLauncher2.set_value(0);

	// Inertial Sensor
	imu.reset();
	int time = pros::millis();
  	int iter = 0;
  	while (imu.is_calibrating()) {
    	printf("IMU calibrating... %d\n", iter);
    	iter += 10;
    	pros::delay(10);
	}
	// Should print after about 2000 ms
	printf("IMU is done calibrating (took %d ms)\n", iter - time);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	// Autonomous selector
	selector::init();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	// Autonomous selector
	selector::init();
}
