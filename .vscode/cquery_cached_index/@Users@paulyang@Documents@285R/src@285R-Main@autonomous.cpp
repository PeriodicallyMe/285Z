#include "285R-Main/initRobot.hpp"
#include "285R-Library/waypoints.hpp"
void red()
{
  flywheel.moveVelocity(185);
  // pros::Task::delay(5000);
  while (flywheel.getActualVelocity() < 180)
    pros::Task::delay(25);
  shoot();

  drive.turnAngle(90_deg);
  drive.waitUntilSettled();

  drive.moveDistance(3.25_ft);
  drive.waitUntilSettled();

  drive.turnAngle(-90_deg);
  drive.waitUntilSettled();

  drive.moveDistance(3.25_ft);
  drive.waitUntilSettled();
}

void blue()
{
  flywheel.moveVelocity(185);
  // pros::Task::delay(5000);
  while (flywheel.getActualVelocity() < 180)
    pros::Task::delay(25);
  shoot();
  //
  // drive.turnAngle(-90_deg);
  // drive.waitUntilSettled();

  // drive.moveDistance(3.25_ft);
  driveL.moveRelative(300, 150);
  // driveR.moveRelative(300, 150);
  drive.waitUntilSettled();

  // drive.turnAngle(90_deg);
  // drive.waitUntilSettled();
  //
  // drive.moveDistance(3.25_ft);
  // drive.waitUntilSettled();
}

void autonomous()
{
  flywheel.moveVelocity(180);
  // pros::Task::delay(5000);
  while (flywheel.getActualVelocity() < 180)
    pros::Task::delay(25);
  shoot();
  pros::delay(1000);

  fl.moveVoltage(6000);
  bl.moveVoltage(6000);
  fr.moveVoltage(6000);
  br.moveVoltage(6000);

  pros::delay(3000);

  fl.moveVoltage(0);
  bl.moveVoltage(0);
  fr.moveVoltage(0);
  br.moveVoltage(0);
}
