#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <webots/PositionSensor.hpp>
// All the webots classes are defined in the "webots" namespace
using namespace webots;

#define Time_Step 32
#define Max_Speed 10

double ps1_val;
double ps2_val;

double radpermeter = 25;
double radperdeg = 0.052;

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Motor *leftMotor =robot->getMotor("motor2");
  Motor *rightMotor =robot->getMotor("motor1");
   int timeStep = (int)robot->getBasicTimeStep();
  //Position sensors
  PositionSensor *ps1 = robot->getPositionSensor("psensor1");
  PositionSensor *ps2 = robot->getPositionSensor("psensor2");
  ps1->enable(Time_Step);
  ps2->enable(Time_Step);
  
   leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  //double encodertarget = radpermeter*2;
  double encodertarget = 90*radperdeg;
 leftMotor->setVelocity(-1);
  rightMotor->setVelocity(1);

  
  while (robot->step(timeStep) != -1) {
  ps1_val = ps1->getValue();
  ps2_val = ps2->getValue();
  if(ps1_val >= encodertarget){
  leftMotor->setVelocity(0);
  rightMotor->setVelocity(0);
  }
  
  std::cout<<"ps1 val "<<ps1_val<<std::endl;
  std::cout<<"ps2 val "<<ps2_val<<std::endl;

}
  delete robot;
  return 0;
  
}