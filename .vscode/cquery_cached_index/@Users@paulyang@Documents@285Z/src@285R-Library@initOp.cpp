#include "285R-Main/initRobot.hpp"

Controller joystick;

pros::ADILineSensor ballSense(1);
Timer timer;

ControllerButton btnShoot												(ControllerDigital::R1);
ControllerButton btnBallIntake									(ControllerDigital::R2);
ControllerButton btnReverseBallSystem						(ControllerDigital::L2);
ControllerButton btnDoubleShot                  (ControllerDigital::X );

ControllerButton btnLUsager                     (ControllerDigital::L2);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its early days

ControllerButton btnLazyMode										(ControllerDigital::up);

ControllerButton btnReverseSystem               (ControllerDigital::A);

bool intakeStyleToggle  {TOGGLE};
bool ballIntakeToggle   {true};
bool driveStyleToggle   {TANK};
bool doubleShot         {false};
bool lUsage             {false};
bool lazy               {false};


void lControl ()
{
  if (btnLUsager.changedToPressed())
    lUsage = !lUsage;

  if (lUsage)
  {
    l.moveAbsolute(-280, 200);
  }
  else
  {
    l.moveAbsolute(0, 200);
  }
}

void intakeStyle ()
{
    if (btnShoot.isPressed())
    {
      ballIndexer.moveVelocity  (600);
      ballIntake.moveVelocity   (600);
      ballIntakeToggle = true;
      if (doubleShot)
        doubleShotControl();
    }
    else if (btnReverseBallSystem.isPressed())
    {
      ballIntake.moveVelocity   (-300);
    }
    else if(btnReverseSystem.isPressed())
    {
      ballIntake.moveVelocity   (-600);
      ballIndexer.moveVelocity  (-200);
    }
    else if(ballIntakeToggle)
    {
      ballIntake.moveVelocity   (600);
      ballIndexer.moveVelocity  (0);
    }
    else
    {
      ballIndexer.moveVelocity	(0);
      ballIntake.moveVelocity	  (0);
    }
//ballSense code (prototype)
    if (ballSense.get_value() < 615) {
      timer.placeHardMark();
    } else {
      timer.clearHardMark();
    }

    if (timer.getDtFromHardMark() >= 300_ms) {
      timer.clearHardMark();
      ballIntakeToggle = false;
    }
  }

void ballControl ()
{
  if (btnBallIntake.changedToPressed())
    ballIntakeToggle = !ballIntakeToggle;

  if (btnDoubleShot.changedToPressed())
  {
    doubleShot = true;
    joystick.setText(0, 0, "Double Shot On");
  }

  intakeStyle();
}

void doubleShotControl ()
{
  if (flywheel.getTargetVelocity() - flywheel.getActualVelocity() > 15 && doubleShot)
  {
    doubleShot = false;

    ballIntake.moveVelocity(0);
    ballIndexer.moveVelocity(0);

    flywheel.moveVelocity(140);
    while (flywheel.getActualVelocity() <= 138)
      pros::Task::delay(10);

    ballIntake.moveVelocity(420);
    ballIndexer.moveVelocity(200);

    pros::Task::delay(500);

    joystick.clearLine(0);
  }
}

void lazyMode ()
{
  drive.stop();

  driveL.tarePosition();
  driveR.tarePosition();

  driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
  driveR.setBrakeMode(AbstractMotor::brakeMode::hold);

  pros::Task::delay(500);

  driveL.moveAbsolute(0, 200);
  driveR.moveAbsolute(0, 200);

  joystick.setText(0, 0, "Active Brake: On");
}

void doArcade ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::brake);
    driveR.setBrakeMode(AbstractMotor::brakeMode::brake);
    drive.arcade
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightX)
    );
  }
  else
    lazyMode();
}

void doTank ()
{
  if (!lazy)
  {
    driveL.setBrakeMode(AbstractMotor::brakeMode::hold);
    driveR.setBrakeMode(AbstractMotor::brakeMode::hold);
    drive.tank
    (
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightY)
    );
  }
  else
    lazyMode();
}

void driveStyle ()
{
  doTank();
}
