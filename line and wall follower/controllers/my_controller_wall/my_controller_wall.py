
from controller import Robot

def run_robot(robot):

    # get the time step of the current world.
    timestep = int(robot.getBasicTimeStep())
    max_speed= 6.28
    
    # You should insert a getDevice-like function in order to get the
    # instance of a device of the robot. Something like:
    #  motor = robot.getMotor('motorname')
    #  ds = robot.getDistanceSensor('dsname')
    #  ds.enable(timestep)
    
    left_motor = robot.getMotor('left wheel motor')
    right_motor = robot.getMotor('right wheel motor')
    
    left_motor.setPosition(float('inf'))
    left_motor.setVelocity(0.0)
    
    right_motor.setPosition(float('inf'))
    right_motor.setVelocity(0.0)
    
    prox_sensors = []
    for ind in range(8):
        sensor_name= "ps"+ str(ind)
        prox_sensors.append(robot.getDistanceSensor(sensor_name))
        prox_sensors[ind].enable(timestep)
    
    # Main loop:
    # - perform simulation steps until Webots is stopping the controller
    while robot.step(timestep) != -1:
        # Read the sensors:
        # Enter here functions to read sensor data, like:
        #  val = ds.getValue()
        for ind in range(8):
            print("ind: {}, val: {}".format(ind, prox_sensors[ind].getValue()))
        
        left_wall =  prox_sensors[5].getValue() > 80
        left_corner = prox_sensors[5].getValue() > 100
        right_wall = prox_sensors[2].getValue() > 80
        right_corner = prox_sensors[2].getValue() > 100
        
        left_speed = 3
        right_speed = 3
        
        """target = 110
        e = 0
        prev_e = 0
        total_e = 0
        
        if prox_sensors[2].getValue() >80:
            print('Right Wall')
            position = prox_sensors[2].getValue()
            e = (position - target)*0.001
            total_e = total_e + e
            prev_e = e
            
         
        if prox_sensors[5].getValue() >80:
            print('Left Wall')
            position = prox_sensors[5].getValue()
            e = (target - position)*0.001
            total_e = total_e + e
            prev_e = e
            
        control = e + 0.01*(e- prev_e) + 0*total_e"""
        
        if right_wall:
        
            if right_corner:
                print('Right Corner')
                left_speed= max_speed/8
                right_speed= max_speed
            
            else:
                print('Right Wall')
                left_speed= max_speed
                right_speed= max_speed
        
        elif left_wall:
        
            if left_corner:
                print('Left Corner')
                left_speed= max_speed
                right_speed= max_speed/8
            
            else:
                print('Left Wall')
                left_speed= max_speed
                right_speed= max_speed
        
        else:  
            x= prox_sensors[2].getValue() - prox_sensors[5].getValue()
                
            if x>=0:
                print('Oops!! Missed the right wall!')
                left_speed = max_speed
                right_speed = max_speed/6
            else:
                print('Oops!! Missed the left wall!')
                left_speed = max_speed/6
                right_speed = max_speed
            
        
        left_motor.setVelocity(left_speed)
        right_motor.setVelocity(right_speed)
        
        
        # Process sensor data here.
    
        # Enter here functions to send actuator commands, like:
        #  motor.setPosition(10.0)
        pass
    
    # Enter here exit cleanup code.

if __name__ == "__main__":

    # create the Robot instance.
    my_robot = Robot()
    run_robot(my_robot)