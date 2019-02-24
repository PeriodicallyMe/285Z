#include "285R-Main/initRobot.hpp"
#include "285R-Library/waypoints.hpp"


const bool fwd {false};
const bool bwd {true};
//true means backwards, false means forwards

void redFront()
{
  flywheel.moveVelocity(185);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);
  profile.removePath("Ball");

  profile.generatePath({hpRed, redBall}, "High Flag Pivot");
  profile.setTarget("High Flag Pivot", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  profile.removePath("High FLag Pivot");

  aut.setMaxVelocity(50);
  aut.turnAngle(-91_deg);
  aut.setMaxVelocity(200);
  shoot();
  ballIntake.moveVelocity(600);

  profile.generatePath({hRed, mRed}, "Mid Flag");
  profile.setTarget("Mid Flag", fwd);
  profile.waitUntilSettled();
  profile.removePath("Mid Flag");
  ballIndexer.moveVelocity(200);
  pros::Task::delay(500);
  ballIndexer.moveVelocity(0);

  profile.generatePath({mRed, lRed}, "Low Flag");
  profile.setTarget("Low Flag", fwd);
  profile.waitUntilSettled();
  profile.removePath("Low Flag");

  ballIndexer.moveRelative(60, 400); //keeps ball in indexer if recycles

  aut.moveDistance(-1.9_ft);
  aut.turnAngle(85_deg);
  ballIntake.moveVelocity(-250);                          //> In autonomous the robot will not go past here

  profile.generatePath({Point{11.0_ft, 9.0_ft, 0.0_deg}, Point{8.5_ft, 9_ft, 0_deg}}, "Flip Cap p2");
  profile.setTarget("Flip Cap p2", fwd);
  profile.waitUntilSettled();
  profile.setTarget("Flip Cap p2", bwd);
  // aut.setMaxVelocity(150);
  // aut.moveDistance(2.55_ft);
  // aut.setMaxVelocity(200);
  // ballIntake.moveVelocity(0);
  // aut.turnAngle(-55_deg);
  // aut.moveDistance(3_ft);
}

void blueFront()
{
  flywheel.moveVelocity(185);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({initBlue, blueBall}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);

  profile.generatePath({Point{10.55_ft, 7.0_ft, 0.0_deg}, blueBall}, "High Flag Pivot");
  profile.setTarget("High Flag Pivot", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  profile.removePath("High FLag Pivot");

  aut.setMaxVelocity(50);
  aut.turnAngle(96_deg);
  aut.setMaxVelocity(200);
  shoot();
  ballIntake.moveVelocity(600);

  profile.generatePath({hBlue, mBlue}, "Mid Flag");
  profile.setTarget("Mid Flag", fwd);
  profile.waitUntilSettled();
  profile.removePath("Mid Flag");
  ballIndexer.moveVelocity(600);
  pros::Task::delay(500);
  ballIndexer.moveVelocity(0);
  profile.generatePath({mBlue, lBlue}, "Low Flag");
  profile.setTarget("Low Flag", fwd);
  profile.waitUntilSettled();

  ballIndexer.moveRelative(60, 400); //keeps ball in indexer if recycles

  aut.moveDistance(-2_ft);
  aut.turnAngle(-95_deg);
  ballIntake.moveVelocity(-250);

  profile.generatePath({Point{11_ft, 9_ft, 0_deg}, Point{8.85_ft, 9_ft, 0_deg}}, "Flip Cap p2");
  profile.setTarget("Flip Cap p2", fwd);
  profile.waitUntilSettled();
  profile.setTarget("Flip Cap p2", bwd);

  // aut.setMaxVelocity(150);
  // aut.moveDistance(2.55_ft);
  // aut.setMaxVelocity(200);
  // ballIntake.moveVelocity(0);
  // aut.turnAngle(59_deg);
  // aut.moveDistance(3_ft);
}

void redBack()
{
  flywheel.moveVelocity(172);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({Point{1_ft, 3_ft, 0_deg}, Point{4.75_ft, 3_ft, 0_deg}}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);

  profile.setTarget("Ball", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  aut.setMaxVelocity(50);
  turn(left);
  aut.setMaxVelocity(200);

  profile.generatePath({Point{1_ft, 3_ft, 90_deg}, Point{1_ft, 5_ft, 90_deg}}, "Middle Column");
  profile.setTarget("Middle Column", fwd);
  profile.waitUntilSettled();

  aut.setMaxVelocity(50);
  aut.turnAngle(29.2_deg);
  aut.setMaxVelocity(200);
  pros::Task::delay(500);
  ballIntake.moveVelocity(600);
  ballIndexer.moveVelocity(600);
  pros::Task::delay(225);
  ballIndexer.moveVelocity(0);

  flywheel.moveVelocity(150);
  pros::Task::delay(3000);
  ballIndexer.moveVelocity(600);
  pros::Task::delay(200);

  aut.turnAngle(59.75_deg);
  ballIntake.moveVelocity(0);
  ballIndexer.moveVelocity(0);
  aut.moveDistance(4.5_ft);
}
void blueBack()
{
  flywheel.moveVelocity(172);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({Point{11_ft, 3_ft, 0_deg}, Point{7.25_ft, 3_ft, 0_deg}}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);

  profile.setTarget("Ball", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  aut.setMaxVelocity(50);
  aut.turnAngle(93_deg);
  aut.setMaxVelocity(200);

  profile.generatePath({Point{11_ft, 3_ft, 90_deg}, Point{11_ft, 5_ft, 90_deg}}, "Middle Column");
  profile.setTarget("Middle Column", fwd);
  profile.waitUntilSettled();

  aut.setMaxVelocity(50);
  aut.turnAngle(-25.5_deg);
  aut.setMaxVelocity(200);
  pros::Task::delay(500);
  ballIntake.moveVelocity(600);
  ballIndexer.moveVelocity(600);
  pros::Task::delay(200);
  ballIndexer.moveVelocity(0);

  flywheel.moveVelocity(148);
  pros::Task::delay(3500);
  ballIndexer.moveVelocity(600);
  pros::Task::delay(200);

  aut.turnAngle(-65_deg);
  aut.moveDistance(4.5_ft);

  ballIntake.moveVelocity(0);
  ballIndexer.moveVelocity(0);
}
void skills()
{
  flywheel.moveVelocity(185);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({initRed, redBall}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);
  profile.removePath("Ball");

  profile.generatePath({hpRed, redBall}, "High Flag Pivot");
  profile.setTarget("High Flag Pivot", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  profile.removePath("High FLag Pivot");

  aut.setMaxVelocity(50);
  aut.turnAngle(-91_deg);
  aut.setMaxVelocity(200);
  shoot();
  ballIntake.moveVelocity(600);

  profile.generatePath({hRed, mRed}, "Mid Flag");
  profile.setTarget("Mid Flag", fwd);
  profile.waitUntilSettled();
  profile.removePath("Mid Flag");
  ballIndexer.moveVelocity(200);
  pros::Task::delay(500);
  ballIndexer.moveVelocity(0);

  profile.generatePath({mRed, lRed}, "Low Flag");
  profile.setTarget("Low Flag", fwd);
  profile.waitUntilSettled();
  profile.removePath("Low Flag");

//  ballIndexer.moveRelative(70, 400); //keeps ball in indexer if recycles

  //profile.generatePath({cppRed, lRed}, "Flip Cap p1");
  aut.moveDistance(-1.9_ft);
  aut.turnAngle(85_deg);
  ballIntake.moveVelocity(-300);                          //> In autonomous the robot will not go past here

  profile.generatePath({cpRed, cRed}, "Flip Cap p2");
  profile.setTarget("Flip Cap p2", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  profile.setTarget("Flip Cap p2", bwd);
  profile.waitUntilSettled();
  profile.removePath("Flip Cap p2");
  turn(right);
  aut.setMaxVelocity(100);
  aut.moveDistance(3.9_ft);
  // profile.generatePath({cpRed, Point{1_ft, 5_ft, 0_deg}}, "Platform Align");
  // profile.setTarget("Platform Align", fwd);
  // profile.waitUntilSettled();
  // profile.removePath("Platform Align");
  aut.turnAngle(-95_deg);
  pros::Task::delay(500);

  // profile.generatePath({Point{1_ft, 5_ft, 0_deg}, Point{6_ft, 5_ft, 0_deg}}, "Center Platform");
  // profile.setTarget("Center Platform", fwd);
  // profile.waitUntilSettled();
  aut.moveDistance(6.5_ft);

  fl.setBrakeMode(AbstractMotor::brakeMode::hold);
  fr.setBrakeMode(AbstractMotor::brakeMode::hold);
  bl.setBrakeMode(AbstractMotor::brakeMode::hold);
  br.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void autonomous()
{
  pros::Task::delay(500);
  redBack();
}
