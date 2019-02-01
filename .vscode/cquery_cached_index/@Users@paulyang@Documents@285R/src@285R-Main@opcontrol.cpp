#include "285R-Library/GUI.hpp"
#include "285R-Main/initRobot.hpp"
#include "285R-Library/odometry.hpp"

Controller boybick;

void opcontrol()
{
  // pros::lcd::initialize();
  // AngleTracker testTracker {6.625, 6.625, 0};
  // gui285R::brainPower(testTracker.getAngle(false));

  l.tarePosition();
  while(ONLINE)
  {
    ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);
    ballIntake.setBrakeMode(AbstractMotor::brakeMode::hold);
    // testTracker.track();
    // std::string angle = std::to_string(testTracker.getAngle(true));
    // boybick.setText(0, 0, angle);
    autTest();

    flywheel.moveVelocity(185);

    if (btnLazyMode.changedToPressed())
      lazy = !lazy;

    driveStyle();

    doubleShotControl();
    ballControl();
    lControl();
  }
}
