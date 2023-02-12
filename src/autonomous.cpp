#include "main.h"

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

    if (selector::auton == 1 || selector::auton == -1) {        // Left side match auton
        // Set the odometric state to zero
        chassis->setState({0_in, 0_in, 0_deg});
        
        // Step 1
        chassis->driveToPoint({1_in, 0_in});
    }
    
    else if (selector::auton == 2 || selector::auton == -2) {   // Right side match auton
        // Set the odometric state to zero
        chassis->setState({0_in, 0_in, 0_deg});

        // Step 1
        chassis->driveToPoint({1_in, 0_in});
    }
    
    else if (selector::auton == 0) {                            // Skills auton
        // Set the odometric state to zero
        chassis->setState({0_in, 0_in, 0_deg});

        // Step 1
        chassis->driveToPoint({1_in, 0_in});

        // Examples:
        // turn 45 degrees and drive approximately 1.4 ft
        //chassis->driveToPoint({1_ft, 1_ft});
        // turn approximately 45 degrees to end up at 90 degrees
        //chassis->turnToAngle(90_deg);
        // turn approximately -90 degrees to face {5_ft, 0_ft} which is to the north of the robot
        //chassis->turnToPoint({5_ft, 0_ft});
    }
}
