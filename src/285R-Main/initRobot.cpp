#include "285R-Main/initRobot.hpp"

Motor ballIntake  (8, true,  AbstractMotor::gearset::blue );
Motor ballIndexer (9, true, AbstractMotor::gearset::green);
Motor flywheel    (14, true, AbstractMotor::gearset::green);
Motor l           (7, true,  AbstractMotor::gearset::green);

Motor fl           (3, false,  AbstractMotor::gearset::green);
Motor bl           (11, false,  AbstractMotor::gearset::green);
Motor fr           (2, true,  AbstractMotor::gearset::green);
Motor br           (4, true,  AbstractMotor::gearset::green);


ChassisControllerIntegrated drive = ChassisControllerFactory::create
(
  {3, 11},
  {-2, -4},
  AbstractMotor::gearset::green,
  {4_in, 9.78_in}
);

MotorGroup driveL = MotorGroup({3, 11});
MotorGroup driveR = MotorGroup({-2, -4});

//driveL.setEncoderUnits(AbstractMotor::encoderUnits::_in);
