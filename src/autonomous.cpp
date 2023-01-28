#include "autoSelect/selection.h"
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
    if (selector::auton == 1 || selector::auton == -1) {
        // Run auton #1
    }
    
    else if (selector::auton == 2 || selector::auton == -2) {
        // Run auton #1
    }
    
    else if (selector::auton == 0) {
        // Skills auton
    }
}
