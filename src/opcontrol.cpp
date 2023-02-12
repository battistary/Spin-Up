#include "main.h"
#include "okapi/api/control/util/controllerRunner.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "pros/misc.h"
#include <memory>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Initialize string launcher
	stringLauncher1.set_value(0);
	stringLauncher2.set_value(0);

	// Display gif image on brain screen
	static Gif gif("/usd/logo_unstretched.gif", lv_scr_act());

	while(true) {
		// Control drivetrain
		chassis->getModel()->arcade(
			controller1.getAnalog(ControllerAnalog::leftY),
			controller1.getAnalog(ControllerAnalog::rightX));
		// Control intake & rollerRoller
		setIntakeMotor();
		// Control flywheel
		setFlywheelMotor();
		// Control stringLaunchers
		setStringLaunchers();
		pros::delay(10);
	}
}
