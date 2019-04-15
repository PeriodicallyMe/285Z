#include "285R-Main/initRobot.hpp"
#include "285R-Library/waypoints.hpp"


const bool fwd {false};
const bool bwd {true};
//true means backwards, false means forwards

const bool oneBall {false};
const bool twoBalls {true};


void redFront()
{
  flywheel.moveVelocity(555);
  ballIntake.moveVelocity(600);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({initRed, redBall}, "Ball"); //gets ball
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();

  profile.setTarget("Ball", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  profile.removePath("Ball");
  turn(-48_deg,50);

  profile.generatePath({Point{1_ft, 7_ft, 45_deg}, Point{2.5_ft, 8.5_ft, 45_deg}}, "Cap Scrape"); //goes forward to cap to scrape
  profile.setTarget("Cap Scrape");
  pros::Task::delay(750);
  shoot(twoBalls); //double shot middle column
  profile.waitUntilSettled();
  profile.removePath("Cap Scrape");

  l.moveAbsolute(130, 50);
  ballIntake.moveVelocity(600);

  // aut.setMaxVelocity(100);
  profile.generatePath({Point{1_ft, 7_ft, 45_deg}, Point{2.8_ft, 8.8_ft, 45_deg}}, "Left Column");
  profile.setTarget("Left Column", bwd);
  pros::Task::delay(100);
  shoot(twoBalls);
  profile.waitUntilSettled();
//  l.moveAbsolute(0,50); //resets scraper
  profile.removePath("Left Column");
  aut.setMaxVelocity(200);

  turn(-43_deg, 50); //turns to face left column
  turn(-2_deg, 50); //readjusts to go straight
  profile.generatePath({hpRed, Point{1_ft, 10_ft, 0_deg}}, "Left Low Flag");
  profile.setTarget("Left Low Flag");
  profile.waitUntilSettled();

  l.moveAbsolute(90, 200);
  profile.generatePath({Point{1_ft, 9_ft, 90_deg}, lRed}, "Middle Low Flag P1");
  profile.setTarget("Middle Low Flag P1", bwd);
  profile.waitUntilSettled();
  profile.removePath("Middle Low Flag P1");
  turn(90_deg, 100);

  profile.generatePath({Point{1_ft, 9_ft, 0_deg}, Point{5.2_ft, 11_ft, 90_deg}}, "Middle Low Flag P2");
  profile.setTarget("Middle Low Flag P2");
  profile.waitUntilSettled();
  l.moveAbsolute(90, 200);
  l.moveAbsolute(0, 200);
}

void blueFront()
{
  //convert to blue please (this is red rn)
  // flywheelControl(2775);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({initBlue, blueBall}, "Ball"); //gets ball
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);
  profile.removePath("Ball");

  profile.generatePath({Point{10_ft, 8_ft, 135_deg}, blueBall}, "Middle Column"); //goes to pos to shoot middle column
  profile.setTarget("Middle Column", bwd);
  profile.waitUntilSettled();
  profile.removePath("Middle Column");
  ballIntake.moveVelocity(0);
  turn(90_deg, 50); //turns to face middle column

  profile.generatePath({Point{2_ft, 8_ft, 45_deg}, Point{2.5_ft, 8.5_ft, 45_deg}}, "Cap Scrape"); //goes forward to cap to scrape
  profile.setTarget("Cap Scrape");
  shoot(twoBalls); //double shot middle column
  profile.waitUntilSettled();
  profile.removePath("Cap Scrape");

  l.moveAbsolute(130, 200); //deploy scraper
  ballIntake.moveVelocity(600);

  profile.generatePath({Point{1_ft, 7_ft, 45_deg}, Point{2.5_ft, 8.5_ft, 45_deg}}, "Left Column");
  profile.setTarget("Left Column", bwd);
  profile.waitUntilSettled();
  l.moveAbsolute(0,200); //resets scraper
  profile.removePath("Left Column");

  turn(-43_deg, 50); //turns to face left column
  shoot(twoBalls); //double shot
  turn(-2_deg, 50); //readjusts to go straight
  profile.generatePath({hpRed, lRed}, "Left Low Flag");
  profile.setTarget("Left Low Flag");
  profile.waitUntilSettled();

  l.moveAbsolute(90, 200);
  profile.generatePath({Point{1_ft, 9_ft, 90_deg}, lRed}, "Middle Low Flag P1");
  profile.setTarget("Middle Low Flag P1", bwd);
  profile.waitUntilSettled();
  profile.removePath("Middle Low Flag P1");
  turn(90_deg, 100);

  profile.generatePath({Point{1_ft, 9_ft, 0_deg}, Point{5.2_ft, 11_ft, 90_deg}}, "Middle Low Flag P2");
  profile.setTarget("Middle Low Flag P2");
  profile.waitUntilSettled();
  l.moveAbsolute(90, 200);
  l.moveAbsolute(0, 200);
}

void redBack()
{
  // flywheelControl(2580);
  ballIndexer.setBrakeMode(AbstractMotor::brakeMode::hold);

  profile.generatePath({Point{1_ft, 3_ft, 0_deg}, Point{4.75_ft, 3_ft, 0_deg}}, "Ball");
  profile.setTarget("Ball", fwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(600);

  profile.setTarget("Ball", bwd);
  profile.waitUntilSettled();
  ballIntake.moveVelocity(0);
  aut.setMaxVelocity(50);
  turn(90_deg, 50);
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

//  flywheel.moveVelocity(150);
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
  // flywheelControl(2580);
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

//  flywheel.moveVelocity(148);
  pros::Task::delay(3500);
  ballIndexer.moveVelocity(600);
  pros::Task::delay(200);

  aut.turnAngle(-65_deg);
  aut.moveDistance(4.5_ft);

  ballIntake.moveVelocity(0);
  ballIndexer.moveVelocity(0);
}

void redBackDescore ()
{
  // flywheelControl(2775);
  ballIntake.moveVelocity(600);
  profile.generatePath({Point{1_ft, 3_ft, 0_deg}, Point{5_ft, 3_ft, 0_deg}}, "Red Ball descore");
  profile.setTarget("Red Ball descore");
  profile.waitUntilSettled();

  turn(-60_deg, 50);
  ballIntake.moveVelocity(0);
  shoot(twoBalls);

  turn(60_deg, 50);
  profile.generatePath({Point{5_ft, 3_ft, 0_deg}, Point{4_ft, 3_ft, 0_deg}}, "Below parking red");
  profile.setTarget("Below Parking red");
  profile.waitUntilSettled();

  turn(-90_deg, 100);
  profile.generatePath({Point{4_ft, 3_ft, 0_deg}, Point{4_ft, 5.5_ft, 0_deg}}, "Park red");
  profile.setTarget("Park red");
  profile.waitUntilSettled();
}

void blueBackDescore ()
{
  // flywheelControl(2775);
  ballIntake.moveVelocity(600);

  profile.generatePath({Point{11_ft, 3_ft, 0_deg}, Point{7_ft, 3_ft, 0_deg}}, "Blue Ball descore");
  profile.setTarget("Blue Ball descore");
  profile.waitUntilSettled();

  turn(60_deg, 50);
  ballIntake.moveVelocity(0);
  shoot(twoBalls);
  turn(-60_deg, 50);

  profile.generatePath({Point{7_ft, 3_ft, 0_deg}, Point{6_ft, 3_ft, 0_deg}}, "Below parking blue");
  profile.setTarget("Below Parking blue");
  profile.waitUntilSettled();

  turn(90_deg, 50);
  profile.generatePath({Point{6_ft, 3_ft, 0_deg}, Point{6_ft, 5.5_ft, 0_deg}}, "Park blue");
  profile.setTarget("Park blue");
  profile.waitUntilSettled();
}

void skills()
{
  // flywheelControl(2775);
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
  profile.removePath("High Flag Pivot");

  aut.setMaxVelocity(50);
  aut.turnAngle(-91_deg);
  aut.setMaxVelocity(200);
  shoot(twoBalls);
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
  turn(90_deg, 50);
  aut.setMaxVelocity(100);
  aut.moveDistance(3.9_ft);

  aut.turnAngle(-95_deg);
  pros::Task::delay(500);

  aut.moveDistance(6.5_ft);

  fl.setBrakeMode(AbstractMotor::brakeMode::hold);
  fr.setBrakeMode(AbstractMotor::brakeMode::hold);
  bl.setBrakeMode(AbstractMotor::brakeMode::hold);
  br.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void autonomous()
{
  redFront();
}
