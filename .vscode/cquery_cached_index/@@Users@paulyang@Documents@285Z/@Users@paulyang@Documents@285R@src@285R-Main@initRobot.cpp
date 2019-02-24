#include "285R-Main/initRobot.hpp"

Motor ballIntake  (5, true,  AbstractMotor::gearset::blue );
Motor ballIndexer (6, true, AbstractMotor::gearset::green);
Motor flywheel    (7, true, AbstractMotor::gearset::green);
Motor l           (9, true,  AbstractMotor::gearset::green);

Motor fl           (1, false,  AbstractMotor::gearset::green);
Motor bl           (2, false,  AbstractMotor::gearset::green);
Motor fr           (3, true,  AbstractMotor::gearset::green);
Motor br           (11, true,  AbstractMotor::gearset::green);


ADILineSensor ballSense(A);
ADIPotentiometer autonSelect (H);


ChassisControllerIntegrated drive = ChassisControllerFactory::create
(
  {1, 2},
  {-3, -11},
  AbstractMotor::gearset::green,
  {4.125_in, 9.78_in}
);

MotorGroup driveL = MotorGroup({1, 2});
MotorGroup driveR = MotorGroup({-3, -11});

//driveL.setEncoderUnits(AbstractMotor::encoderUnits::_in);
