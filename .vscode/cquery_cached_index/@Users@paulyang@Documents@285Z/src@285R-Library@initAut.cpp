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

const bool right {1};
const bool left  {0};

void shoot ()
{
  ballIndexer.moveVelocity(600);

  pros::Task::delay(250);

  ballIndexer.moveVelocity(0);
}

void turn (bool direction)
{

  if (direction)
  aut.turnAngle(90_deg);
  else
  aut.turnAngle(-90_deg);
}
