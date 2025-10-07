#include "EZ-Template/util.hpp"
#include "globals.hpp"
#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///

void default_constants() 
{
  chassis.pid_drive_constants_set(13, 0, 99.75);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0, 22.5);
  chassis.pid_turn_constants_set(7.25, 0, 78,15);            // Turn constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(8.5, 0.0, 60);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.5, 0.0, 33);


  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.95);

  chassis.odom_look_ahead_set(10_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);
  chassis.drive_imu_scaler_set(1.001);

}

//school field: 2_in, hom: 0
///
// Drive Example
///
okapi::QLength MLoffset = 2.5_in;
okapi::QLength odomDrift1 = 3.575_in;
okapi::QLength centerGoalOffset = 2.5_in;
okapi::QLength MLoffset2 = 2.5_in;


double centerGoalOffsetT = 2.5;
double MLoffsetT = 2.5;
double MLoffsetT2 = 2.5;
double odomDriftT1 = 3.575;
void skills() 
{
  

  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches
  globController = 10;
  redirect.set_value(false);
  trapDoor.set(false);
  chassis.pid_odom_set({{0_in, 15_in}, fwd, 110}, false); //initial movement
  chassis.pid_wait();
  chassis.pid_turn_set({10,15}, fwd,  110); //turns right
  chassis.pid_wait();
  chassis.pid_odom_set({{30_in - MLoffset, 15_in}, fwd, 110},false);  //moves forward to align with matchload
  chassis.pid_wait();
  matchLoads1.set(true); 
  chassis.pid_turn_set({30 - MLoffsetT, 8.5}, fwd, 110); //turns right to face matchload
  chassis.pid_wait();
  chassis.pid_odom_set(8.5,110, false); //backs away from =
  chassis.pid_wait();
  pros::delay(1000); //waits at matchload
  chassis.pid_odom_set(-5,127, false); //backs away from matchload
  chassis.pid_wait();
  matchLoads1.set(false); 
  chassis.pid_turn_set({7.25,39}, fwd,  110); //turns to face four blocks
  chassis.pid_wait();
  chassis.pid_odom_set({{7.25_in, 39_in}, fwd, 110},true);  //drives to four blocks
  chassis.pid_wait();
  chassis.pid_turn_set({12,62}, fwd,  110); //turns to face four blocks
  chassis.pid_wait();
  chassis.pid_odom_set({{12_in, 62_in}, fwd, 110},true);  //drives to four blocks
  chassis.pid_wait();
  chassis.pid_turn_set({19,62}, fwd,  110); //turns to face four blocks
  chassis.pid_wait();
  chassis.pid_odom_set(7,127, false); //backs away from blocks
  chassis.pid_wait();
  chassis.pid_odom_set(-5,127, false); //backs away from blocks
  chassis.pid_wait();
  chassis.pid_turn_set({1.25,81}, fwd,  110); //turns to face other 4 blocks
  chassis.pid_wait();
  chassis.pid_odom_set({{1.25_in, 81_in}, fwd, 110},true);  //drives to other four blocks
  chassis.pid_wait();
  chassis.pid_turn_set({-3,77}, fwd,  110); // turns to bottom goal
  chassis.pid_wait(); 
  chassis.pid_odom_set(10,127, false); //backs away from blocks
  chassis.pid_wait();
  globController = 4;
  pros::delay(2000);
  chassis.pid_odom_set({{30_in - centerGoalOffset - odomDrift1, 107_in}, rev, 110},false);  //backs away from bottom goal to long goal
  chassis.pid_wait();
  globController = 10;
  chassis.pid_turn_set({30 - centerGoalOffsetT - odomDriftT1, 97}, fwd, 110); //turns towards long goal (forwards)
  chassis.pid_wait();
  chassis.pid_odom_set(14,110, false); //backs away from blocks
  chassis.pid_wait();
  globController = 3;
  pros::delay(2000);//waits at top goal
  chassis.pid_odom_set({{30_in - MLoffset2 - odomDrift1, 107_in}, rev, 110},false);  //backs away from bottom goal to long goal
  chassis.pid_wait();
  globController = 10;
  chassis.pid_turn_set({30 - MLoffsetT2 - odomDriftT1,125}, fwd,  110);
  chassis.pid_wait();
  matchLoads1.set(true);
  chassis.pid_odom_set(18,127, false);//backs away from long goal
  chassis.pid_wait();
  pros::delay(1000); //waits at matchload
  chassis.pid_odom_set(-5,127, false);    //backs away from matchload 2
  chassis.pid_wait(); 
  matchLoads1.set(false);
  chassis.pid_turn_set(90_deg, 95);
  chassis.pid_wait();
  chassis.pid_odom_set({{-3.575_in, 93_in}, fwd, 110},true); // drives to 4 blocks  
  chassis.pid_wait();
 
  /*
  redirect.set_value(false);
  hood.move(-127);
  intake.move(127);
  chassis.pid_drive_set(12_in, 70);
  chassis.pid_wait_quick_chain(); 
  chassis.pid_swing_set(ez::LEFT_SWING, 135_deg, 85);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(23.25_in, 70, true);
  chassis.pid_wait();
  chassis.pid_swing_set(ez::LEFT_SWING, 181_deg, 80);
  chassis.pid_wait();
  pros::delay(200);
  chassis.pid_drive_set(8.88_in, 90, true);
  chassis.pid_wait();
  pros::delay(400);
  chassis.pid_drive_set(-8.85_in, 90, true);
  matchLoads.set_value(true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-3.10_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(8.125_in, 90, true);
  redirect.set_value(true);
  hopper.move(127);
  chassis.pid_wait();
  pros::delay(3000);
  chassis.pid_swing_set(ez::LEFT_SWING, -75_deg, 90);
  chassis.pid_wait();
  hood.move(-127);
  intake.move(127);
  redirect.set_value(false);
  chassis.pid_drive_set(77.5_in, 45, true);
  chassis.pid_wait();
  chassis.pid_turn_set(46.25_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(8.5_in, 90, true);
  chassis.pid_wait();
  hood.move(127);
  */

}

///
// Turn Example
///
void elimsRBRight()
{
  // The first parameter is the target in degrees`````
  // The second parameter is max speed the robot will drive at
  chassis.odom_xyt_set(0_in, 0_in, 15_deg);  
  intake.move(127);
  hopper.move(127);
  chassis.pid_drive_set(20,80,true);
  chassis.pid_wait_quick();
  /*
  chassis.pid_turn_set(90_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(7.75_in, 110, true);
  chassis.pid_wait();
  chassis.pid_swing_set(ez::RIGHT_SWING,180,110);
  chassis.pid_wait();
  chassis.pid_drive_set(20,110,true);
  */
  chassis.pid_turn_set({32.10,0}, fwd,  90);
  chassis.pid_wait(); 
  chassis.pid_odom_set({{32.10_in, 0_in}, fwd, DRIVE_SPEED},true);  
  matchLoads1.set(true);  
  chassis.pid_wait(); 
  chassis.pid_turn_set(180_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(7,110,true);
  chassis.pid_wait();
  pros::delay(1500);
  chassis.pid_drive_set(-19_in, 90, true);
  matchLoads1.set(false);
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(2_in, 90, true);
  chassis.pid_wait();
  hood.move(-127);
  redirect.set_value(true);
  hopper.move(127);
  chassis.pid_wait();
  pros::delay(3000);
}

///
// Combining Turn + Drive
///

int longOffset = 1;
void elimsRBLeft() 
{
    // The first parameter is the target in degrees`````
  // The second parameter is max speed the robot will drive at
  chassis.odom_xyt_set(0_in, 0_in, 15_deg);  
  intake.move(127);
  hopper.move(127);
  chassis.pid_drive_set(47.5,80,true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(-90_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(7.75_in, 110, true);
  chassis.pid_wait();
  chassis.pid_swing_set(ez::RIGHT_SWING,180,110);
  chassis.pid_wait();
  chassis.pid_drive_set(20,110,true);
  chassis.pid_wait();
  chassis.pid_turn_set({-32.10,0}, fwd,  90);
  chassis.pid_wait(); 
  matchLoads1.set(true);
  chassis.pid_odom_set({{-32.10_in, 0_in}, fwd, DRIVE_SPEED},true);  
  chassis.pid_wait(); 
  chassis.pid_turn_set(180_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(7,110,true);
  chassis.pid_wait();
  pros::delay(1500);
  chassis.pid_drive_set(-19_in, 90, true);
  matchLoads1.set(false);
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, 95);
  chassis.pid_wait();
  chassis.pid_drive_set(2_in, 90, true);
  chassis.pid_wait();
  hood.move(-127);
  redirect.set_value(true);
  hopper.move(127);
  chassis.pid_wait();
  pros::delay(3000);

}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() 
{
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
 
  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();


  /*
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
  */
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() 
{
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///

void odom_drive_example() 
{
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.
chassis.pid_turn_set(3600_deg, 110, ez::raw);
chassis.pid_wait();




}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example()
 {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() 
{
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    //chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .