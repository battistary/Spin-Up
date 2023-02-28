#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

// Controllers
okapi::Controller controller1(ControllerId::master);
okapi::Controller controller2(ControllerId::partner);

// Motors
// Each raw encoder count is 0.375 degrees, so there are 960 in one revolution
pros::Motor driveLeftFront(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftCenter(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightCenter(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheel(11, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

// Motor Groups
pros::Motor_Group driveLeft({driveLeftBack, driveLeftCenter, driveLeftFront});
pros::Motor_Group driveRight({driveRightBack, driveRightCenter, driveRightFront});

// ADI Digital Outs
pros::ADIDigitalOut stringLauncher1('A', false);
pros::ADIDigitalOut stringLauncher2('B', false);

// Inertial Sensor
pros::Imu imu(4);

// Chassis Controller
std::shared_ptr<okapi::OdomChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({5, 6, 7}, {16, 17, 20})
        // Speed gearset, 36:48 gear ratio, 3.25" wheel diameter, 10.75" wheel track
        .withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 11.65_in}, imev5BlueTPR})
        //.withDimensions({AbstractMotor::gearset::blue, (48.0 / 36.0)}, {{3.25_in, 10.207_in}, imev5BlueTPR})
        .withGains(
            {0.00063, 0, 0.000013},	// Distance controller gains
            {0.0015, 0, 0.00003})
            //{0.00180, 0, 0.000038}) // Turn controller gains
//           {0.001,   0, 0.0001  })	// Angle controller gains
        .withOdometry() // Use the same scales as the chassis (above) for odometry
        .withMaxVelocity(600)
        .withLogger(
          std::make_shared<Logger>(
            TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            "/ser/sout", // Output to the PROS terminal
            Logger::LogLevel::debug // Most verbose log level
          )
        )
        .buildOdometry();

// Intake Controller
std::shared_ptr<AsyncPositionController<double, double>> intakeController = 
  AsyncPosControllerBuilder()
    .withMotor(9)
    .withMaxVelocity(200)
    .build();
