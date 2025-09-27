#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern pros::Motor intake;
extern pros::Motor hood;
extern pros::Motor hopper;



//pneumatics
extern pros::adi::Pneumatics hoodP;
extern pros::adi::Pneumatics odomPull;
extern pros::adi::Pneumatics redirect;

extern pros::adi::Pneumatics trapDoor;




//Sensors
extern pros::Optical optical_sensorR;
extern pros::Optical optical_sensorL;

extern pros::Rotation rotation_sensor;
extern pros::Distance distance_sensor;
extern pros::adi::DigitalIn limitSwitch;

//Variables
extern bool autonOn;
extern bool spinCase;
extern int alliance;
extern int team;
extern double hue;
extern int globCont;