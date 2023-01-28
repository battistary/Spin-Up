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
	Gif gif("/usd/tipping_point_HD.gif", lv_scr_act());

	// Chassis controller
	std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
			.withMotors({5, 6, 7}, {16, 17, 20})
			// Speed gearset, 2.75" wheel diameter, 11" wheel track
			.withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 11_in}, imev5BlueTPR})
			//.withGains(
			//	{0, 0, 0},	// Distance controller gains
			//	{0, 0, 0},	// Turn controller gains
			//	{0, 0, 0})	// Angle controller gains
			//.withOdometry() // Use the same scales as the chassis (above) for odometry (not worth it without encoders & tracking wheel)
			.build();
		drive->setMaxVelocity(600);

	while(true) {
		// Control drivetrain
		drive->getModel()->arcade(
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
