#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

// Variables
double fw_output = 0.0;
float target_fw_rpm = 0.0;

// Controllers
okapi::Controller controller1(ControllerId::master);
okapi::Controller controller2(ControllerId::partner);

// Motors
// Each raw encoder count is 0.375 degrees, so there are 960 in one revolution
pros::Motor driveLeftFront(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftCenter(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS); // moved from port 6
pros::Motor driveLeftBack(4, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(13, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightCenter(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheel(11, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

// Motor Groups
pros::Motor_Group driveLeft({driveLeftBack, driveLeftCenter, driveLeftFront});
pros::Motor_Group driveRight({driveRightBack, driveRightCenter, driveRightFront});

// ADI Digital Outs
pros::ADIDigitalOut stringLauncher1('A', false);
pros::ADIDigitalOut stringLauncher2('B', false);
pros::ADIDigitalOut blooper('H', false);

// Inertial Sensor
pros::Imu imu(1);

// Chassis Controller PID
std::shared_ptr<okapi::ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({2, 3, 4}, {13, 18, 19})
        // Speed gearset, 36:48 gear ratio, 3.25" wheel diameter, 10.75" wheel track0
        //.withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 25_in}, imev5BlueTPR})
        .withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 10.75_in}, imev5BlueTPR})
        .withGains(
            {0.0015, 0.0, 0.000048},//{0.0015,  0, 0.00008 }, //{0.00063, 0, 0.000014},	// Distance controller gains
            {0.0019,  0, 0.000024}, // Turn controller gains
            {0.0015, 0.0, 0.000048})//{0.001,   0, 0.0001  })	// Angle controller gains
        .withMaxVelocity(600)
        .build();

// Chassis Controller NO PID
std::shared_ptr<okapi::ChassisController> NOPIDchassis =
    ChassisControllerBuilder()
      .withMotors({2, 3, 4}, {13, 18, 19})
      // Speed gearset, 36:48 gear ratio, 3.25" wheel diameter, 10.75" wheel track0
      //.withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 25_in}, imev5BlueTPR})
      .withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 10.75_in}, imev5BlueTPR})
      .withMaxVelocity(600)
      .build();

// Intake Controller
std::shared_ptr<AsyncPositionController<double, double>> intakeController = 
  AsyncPosControllerBuilder()
    .withMotor(9)
    .withMaxVelocity(200)
    .build();
