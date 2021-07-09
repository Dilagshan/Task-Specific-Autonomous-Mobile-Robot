#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <webots/PositionSensor.hpp>
#include <windows.h>
// All the webots classes are defined in the "webots" namespace
using namespace webots;


#define Time_Step 32
#define Max_Speed 10

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Motor *leftMotor =robot->getMotor("motor2");
  Motor *rightMotor =robot->getMotor("motor1");
  
  //Position sensors
 /* PositionSensor *ps1 = robot->getPositionSensor("psensor1");
  PositionSensor *ps2 = robot->getPositionSensor("psensor2");
  ps1->enable(Time_Step);
  ps2->enable(Time_Step);*/
  
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  while (robot->step(Time_Step) != -1) {
  leftMotor->setVelocity(3);
  rightMotor->setVelocity(3);
  
    delete robot;
  return 0;
}  
}