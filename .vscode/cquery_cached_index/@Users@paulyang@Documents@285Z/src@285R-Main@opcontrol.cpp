#include "285R-Library/GUI.hpp"
#include "285R-Main/initRobot.hpp"
#include "285R-Library/odometry.hpp"
#include "/Users/paulyang/Documents/285Z/src/285R-Library/flywheelUtil/flywheel.hpp"


Controller boybick;

void opcontrol()
{
  // pros::lcd::initialize();
  // AngleTracker testTracker {6.625, 6.625, 0};
  // gui285R::brainPower(testTracker.getAngle(false));
  pros::Task intakeThread(lControlTask, (void*)"PROS", TASK_PRIORITY_DEFAULT,
                TASK_STACK_DEPTH_DEFAULT, "Scraper Task");

  l.tarePosition();
  while(ONLINE)
  {
  //  flywheel.moveVelocity(555);
    flywheelControl(2775);
    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    driveStyle();
    ballControl();
    pros::delay(10);
  }
}
