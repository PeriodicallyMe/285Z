#include "285R-Main/initRobot.hpp"

ChassisControllerIntegrated aut = ChassisControllerFactory::create
(
  {1, 2},
  {-3, -11},
  AbstractMotor::gearset::green,
  {4.125_in, 9.625_in}
);

AsyncMotionProfileController profile = AsyncControllerFactory::motionProfile
(
   1.25,
   2.0,
   5.0,
   aut
);


void shoot (bool number)
{
  if(number)
  {
    doubleShotControl();
  }
  else
  {
    ballIndexer.moveVelocity(600);
    ballIntake.moveVelocity(600);

    pros::Task::delay(150);

    ballIndexer.moveVelocity(0);
    ballIntake.moveVelocity(0);
  }
}

void turn (QAngle degrees, float rpm)
{
  aut.setMaxVelocity(rpm);

  aut.turnAngle(degrees);

  aut.setMaxVelocity(200);
}
