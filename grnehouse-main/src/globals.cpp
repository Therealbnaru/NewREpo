#include "globals.hpp"
#include "main.h"
#include "pros/optical.hpp"

pros::Motor intake(-13, pros::v5::MotorGears::blue); // Motor is a reversed green motor on port 4
pros::Motor hood(15, pros::v5::MotorGears::green); // Motor is a normal blue motor on port 16
pros::Motor hopper(14, pros::v5::MotorGears::green); // Motor is a normal green motor on port 10

//Pneumatics
pros::adi::Pneumatics matchLoads('A', true); // Starts clamp in the false (Down) position when the code starts in port A
pros::adi::Pneumatics hoodP('B', false); // Starts tipper in the false (Down) position when the code starts in port A
pros::adi::Pneumatics odomPull('C', true); // Starts clamp in the false (Down) position when the code starts in port A
pros::adi::Pneumatics redirect('H', true);

pros::adi::Pneumatics trapDoor('E', false);

//Sensors


int alliance = 1; // Default alliance is 1 which is red
pros::Optical optical_sensorR(4);
pros::Optical optical_sensorL(16);
double hueR = optical_sensorR.get_hue();
double hueL = optical_sensorL.get_hue();
int proxL = optical_sensorL.get_proximity();
int proxR = optical_sensorR.get_proximity();
bool intakeOff = true;
bool autonOn = true;
int globController = 10;




