#include "285R-Main/initRobot.hpp"

ChassisControllerIntegrated aut = ChassisControllerFactory::create
(
  {3, 11},
  {-2, -4},
  AbstractMotor::gearset::green,
  {4_in, 9.78_in}
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
  ballIntake.moveVelocity(200);
  ballIndexer.moveVelocity(200);

  pros::Task::delay(500);

  ballIntake.moveVelocity(0);
  ballIndexer.moveVelocity(0);
}

void turn (bool direction)
{
  if (direction)
  aut.turnAngle(90_deg);
  else
  aut.turnAngle(-90_deg);
}
