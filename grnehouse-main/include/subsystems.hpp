#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
inline ez::Piston matchLoads1('A', true);//Matchloader
inline ez::Piston trapDoor('E', false);//Trapdoor
inline ez:: Piston odomPull('C', true);//Pulls horizontal odom pod
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');