#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>
#include <webots/PositionSensor.hpp>
#include <windows.h>
// All the webots classes are defined in the "webots" namespace
using namespace webots;

//#define Time_Step 32
#define Max_Speed 10

double ir0_val;
double ir1_val;
double ir2_val;
double ir3_val;
double ir4_val;
double ir5_val;

double ps1_val;
double ps2_val;

//double meterperrad = 0.04;
//double radperdeg = 0.052;

double get_error(){
    return  (3*ir0_val+2*ir1_val+ir2_val-ir3_val-2*ir4_val-3*ir5_val)/30;
}

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Motor *leftMotor =robot->getMotor("motor2");
  Motor *rightMotor =robot->getMotor("motor1");
  
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  //ir sensors
  DistanceSensor *ir0 = robot-> getDistanceSensor("ir0"); 
  DistanceSensor *ir1 = robot-> getDistanceSensor("ir1"); 
  DistanceSensor *ir2 = robot-> getDistanceSensor("ir2"); 
  DistanceSensor *ir3 = robot-> getDistanceSensor("ir3"); 
  DistanceSensor *ir4 = robot-> getDistanceSensor("ir4"); 
  DistanceSensor *ir5 = robot-> getDistanceSensor("ir5"); 
  
  DistanceSensor *ds_right = robot->getDistanceSensor("ds_right");
  DistanceSensor *ds_left = robot->getDistanceSensor("ds_left");
  
    // get the time step of the current world.
  int Time_Step = (int)robot->getBasicTimeStep();
  
  ir0->enable(Time_Step);
  ir1->enable(Time_Step);
  ir2->enable(Time_Step);
  ir3->enable(Time_Step);
  ir4->enable(Time_Step);
  ir5->enable(Time_Step);
  
  ds_right->enable(Time_Step);
  ds_left->enable(Time_Step);
 
  while (robot->step(Time_Step) != -1) {
  
  double ds_right_val = ds_right->getValue();
  double ds_left_val = ds_left->getValue();
    
  ir0_val= ir0->getValue();
  ir1_val= ir1->getValue();
  ir2_val= ir2->getValue();
  ir3_val= ir3->getValue();
  ir4_val= ir4->getValue();
  ir5_val= ir5->getValue();
  
  // Digitalization
   if(ir0_val>700){
    ir0_val = 0;
    }else{
    ir0_val = 1;
    }
    if(ir1_val>700){
    ir1_val = 0;
    }else{
    ir1_val = 1;
    }
    if(ir2_val>700){
    ir2_val = 0;
    }else{
    ir2_val = 1;
    }
    if(ir3_val>700){
    ir3_val = 0;
    }else{
    ir3_val = 1;
    }
    if(ir4_val>700){
    ir4_val = 0;
    }else{
    ir4_val = 1;
    }
    if(ir5_val>700){
    ir5_val = 0;
    }else{
    ir5_val = 1;
    }
  //PID parametres for line following
  double error= get_error();
  double last_error = 0;
  double derivative = error - last_error;
  last_error = error;
  
 // PID parameters for right motor
    double target =750;
    double last_wr_error = 0;
    double r_position = ds_right_val;
    double wr_error = (r_position - target)/10;
    double wr_derivative = wr_error - last_wr_error;
    last_wr_error = wr_error;
   
   //PID parametres for left motor 
    double last_wl_error = 0;
    double l_position = ds_left_val;
    double wl_error = (l_position - target)/10;
    double wl_derivative = wl_error - last_wl_error;
    last_wl_error = wl_error;
    
    
  if((ir0_val==0)&&(ir1_val==0)&&(ir2_val==0)&&(ir3_val==0)&&(ir4_val==0)&&(ir5_val==0)){
     if ((ds_right_val <950)&&(ds_left_val==1000)){
      std::cout << "ds_right: " << ds_right_val <<std::endl;
      std::cout << "wr_error: " << wr_error <<std::endl;
      leftMotor->setVelocity(2+0.5*wr_error+ 0.5*wr_derivative);
      rightMotor->setVelocity(2-0.5*wr_error-0.5*wr_derivative);
      }
     else if((ds_right_val ==1000)&&(ds_left_val<950)){      
      std::cout << "ds_left: " << ds_left_val <<std::endl;
      std::cout << "wl_error: " << wl_error <<std::endl;
      leftMotor->setVelocity(2-0.5*wl_error-0.5*wl_derivative);
      rightMotor->setVelocity(2+0.5*wl_error+0.5*wl_derivative);
      }
      else{
      leftMotor->setVelocity(2);
      rightMotor->setVelocity(2);
      }
      }
  else{ 
  leftMotor->setVelocity(3-25*error-45*derivative);
  rightMotor->setVelocity(3+25*error+45*derivative);

  }
}
  delete robot;
  return 0;
  
}