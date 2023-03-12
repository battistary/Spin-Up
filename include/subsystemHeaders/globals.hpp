#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"

// Controllers
extern okapi::Controller controller1;
extern okapi::Controller controller2;
extern pros::Controller master;

// Motors
extern pros::Motor driveLeftFront;
extern pros::Motor driveLeftCenter;
extern pros::Motor driveLeftBack;
extern pros::Motor driveRightFront;
extern pros::Motor driveRightCenter;
extern pros::Motor driveRightBack;
extern pros::Motor flywheel;
extern pros::Motor intake;

// Motor Groups
extern pros::Motor_Group driveLeft;
extern pros::Motor_Group driveRight;

// ADI Digital Outs
extern pros::ADIDigitalOut stringLauncher1;
extern pros::ADIDigitalOut stringLauncher2;

// Inertial Sensor
extern pros::Imu imu;

// Chassis Controller
extern std::shared_ptr<okapi::ChassisController> chassis;

// Chassis Controller NO PID
extern std::shared_ptr<okapi::ChassisController> NOPIDchassis;

// Intake Controller
extern std::shared_ptr<AsyncPositionController<double, double>> intakeController;
