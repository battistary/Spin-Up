#include "main.h"
#include "pros/adi.hpp"

// Controllers
okapi::Controller controller1(ControllerId::master);
okapi::Controller controller2(ControllerId::partner);

// Motors
pros::Motor driveLeftFront(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftCenter(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightCenter(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheel(11, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

// Motor Groups
pros::Motor_Group driveLeft({driveLeftBack, driveLeftCenter, driveLeftFront});
pros::Motor_Group driveRight({driveRightBack, driveRightCenter, driveRightFront});

// ADI Digital Outs
pros::ADIDigitalOut stringLauncher1('A', false);
pros::ADIDigitalOut stringLauncher2('B', false);

// Inertial Sensor
pros::Imu imu(4);

// Chassis controller
std::shared_ptr<OdomChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({5, 6, 7}, {16, 17, 20})
        // Speed gearset, 36:48 gear ratio, 2.75" wheel diameter, 10.75" wheel track
        .withDimensions({AbstractMotor::gearset::blue, (36.0 / 48.0)}, {{2.75_in, 10.75_in}, imev5BlueTPR})
        .withGains( // CALIBRATE!
            {0.001, 0, 0.0001},	// Distance controller gains
            {0.001, 0, 0.0001},	// Turn controller gains
            {0.001, 0, 0.0001})	// Angle controller gains
        .withOdometry() // Use the same scales as the chassis (above) for odometry (not worth it without encoders & tracking wheel)
        .withMaxVelocity(600)
        .buildOdometry();
