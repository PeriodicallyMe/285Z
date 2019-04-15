#include "285R-Main/initRobot.hpp"

Controller joystick;

pros::ADILineSensor ballSense(1);
Timer timer;

ControllerButton btnShoot												(ControllerDigital::R1);
ControllerButton btnBallIntake									(ControllerDigital::R2);
ControllerButton btnReverseBall       					(ControllerDigital::A);
ControllerButton btnDoubleShot                  (ControllerDigital::X );
ControllerButton btnReverseSystem               (ControllerDigital::Y);

ControllerButton btnHoodToggle                  (ControllerDigital::L2);
ControllerButton btnLUsager                     (ControllerDigital::L1);         //> 'L' refers to the robot's arm which was in the shape of an 'L' in its early days

ControllerButton btnLazyMode										(ControllerDigital::up);


bool intakeStyleToggle  {TOGGLE};
bool ballIntakeToggle   {true};
bool driveStyleToggle   {TANK};
bool doubleShot         {false};
bool lUsage             {false};
bool lazy               {false};
bool hoodToggle         {false};


void lControl ()
{
  joystick.setText(0, 0, std::to_string(l.getPosition()));
  if (btnHoodToggle.changedToPressed())
  {
    hoodToggle = !hoodToggle;
  }
  if (btnLUsager.isPressed())
  {
    l.moveAbsolute(165, 50);
  }
  else if (hoodToggle)
  {
    l.moveAbsolute(-20, 100);
  }
  else if (doubleShot && btnShoot.isPressed())
  {
    doubleShotControl();
  }
  else
  {
    l.moveAbsolute(0,50);
  }
}

void ballControl ()
{
    if (btnBallIntake.changedToPressed())
    {
      ballIntakeToggle = !ballIntakeToggle;
    }
    if (btnShoot.isPressed())
    {
      ballIndexer.moveVelocity  (600);
      ballIntake.moveVelocity   (600);
      ballIntakeToggle = true;
    }
    else if (btnReverseBall.isPressed())
    {
      ballIntake.moveVelocity   (-300);
    }
    else if(btnReverseSystem.isPressed())
    {
      ballIntake.moveVelocity   (-600);
      ballIndexer.moveVelocity  (-600);
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
      ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);
    }
//ballSense code (prototype)
    if (ballSense.get_value() < 615) {
      timer.placeHardMark();
    } else {
      timer.clearHardMark();
    }

    if (timer.getDtFromHardMark() >= 150_ms) {
      timer.clearHardMark();
      ballIntakeToggle = false;
      doubleShot = true;
    }
  }

void lControlTask(void* param) {
  while(true) {
    lControl();
    pros::Task::delay(10);
  }
}

void doubleShotControl()
{
  pros::Task::delay(150);
  l.moveAbsolute(-20, 100);

  pros::Task::delay(150);
  l.moveAbsolute(0, 100);

  doubleShot = false;
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
