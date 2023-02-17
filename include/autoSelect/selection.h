#pragma once

#include <string>

//selector configuration
#define HUE 360
#define DEFAULT 1
#define AUTONS "Turn PD", "Distance PD", "Skills (roller)"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = 213, int default_auton = DEFAULT, const char **autons = b);

}
