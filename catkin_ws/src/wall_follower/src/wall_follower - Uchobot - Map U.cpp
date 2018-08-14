// ROS Libraries
#include "ros/ros.h"
#include "geometry_msgs/Twist.h" // Motor Commands
#include "sensor_msgs/LaserScan.h" // Laser Data
#include "tf/transform_listener.h" // tf Tree


// C++ Libraries
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>

// ROS Publisher:Motor Commands, Subscriber:Laser Data, and Messages:Laser Messages & Motor Messages
ros::Publisher motor_command_publisher;
ros::Subscriber laser_subscriber;
sensor_msgs::LaserScan laser_msg;
geometry_msgs::Twist motor_command;

// Define the robot direction of movement
typedef enum _ROBOT_MOVEMENT {
    STOP = 0,
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT,
    GO_RIGHT,
    GO_LEFT

} ROBOT_MOVEMENT;

// The robot_move function will be called by the laser_callback function each time a laser scan data is received
// This function will accept robot movements and actuate the robot's wheels accordingly
// Keep a low speed for better results
bool robot_move(const ROBOT_MOVEMENT move_type)
{
    if (move_type == STOP) {
        ROS_INFO("[ROBOT] HALT! \n");

        motor_command.angular.z = 0.0;
        motor_command.linear.x = 0.0;
    }

    else if (move_type == FORWARD) {
        ROS_INFO("[ROBOT] Always FORWARD! \n");
        motor_command.angular.z = 0.0;
        motor_command.linear.x = 0.5;
    }

    else if (move_type == BACKWARD) {
        ROS_INFO("[ROBOT] I'm going back! \n");
        motor_command.linear.x = -1.0;
        motor_command.angular.z = 0.0;
    }

    else if (move_type == TURN_LEFT) {
        ROS_INFO("[ROBOT] I'm turning left! \n");
        motor_command.linear.x = 0.0;
        motor_command.angular.z = 1.0;
    }

    else if (move_type == TURN_RIGHT) {
        ROS_INFO("[ROBOT] I'm turning right! \n");
        motor_command.linear.x = 0.0;
        motor_command.angular.z = -1.0;
    }
    else if (move_type == GO_RIGHT) {
        ROS_INFO("[ROBOT] I'm goin right! \n");
        motor_command.linear.x = 0.25;
        motor_command.angular.z = -0.30;
    }
    else if (move_type == GO_LEFT) {
        ROS_INFO("[ROBOT] I'm goin left! \n");
        motor_command.linear.x = 0.25;
        motor_command.angular.z = 0.30;
    }
    else {
        ROS_INFO("[ROBOT_MOVE] Move type wrong! \n");
        return false;
    }

    //Publish motor commands to the robot and wait 10ms
    motor_command_publisher.publish(motor_command);
    usleep(10);
    return true;
}

bool following_wall = false;
bool thats_a_door = false;
bool crashed = false;

// The laser_callback function will be called each time a laser scan data is received
void laser_callback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
    // Read and process laser scan values
    laser_msg = *scan_msg;
    std::vector<float> laser_ranges;
    laser_ranges = laser_msg.ranges;
    size_t range_size = laser_ranges.size();
    float left_side = 0.0, right_side = 0.0;
    float right_side_lateral = 0.0, right_side_central = 0.0;
    float range_min = laser_msg.range_max, range_max = laser_msg.range_min;
    
    /*int nan_count = 0;
    for (size_t i = 0; i < range_size; i++) {
        if (laser_ranges[i] < range_min) {
            range_min = laser_ranges[i];
        }

        if (std::isnan(laser_ranges[i])) {
            nan_count++;
        }
        if (i < range_size / 4) {
	    right_side_lateral += laser_ranges[i];
            if (laser_ranges[i] > range_max) {
                range_max = laser_ranges[i];
            }
        }
	if(range_size / 4 < i < range_size / 2){
	    right_side_central += laser_ranges[i];
	}
        if (i > range_size / 2) {
            left_side += laser_ranges[i];
        }
        else {
            right_side += laser_ranges[i];
        }
    }
    printf("Valor de range_size: %lu \n",range_size);
    printf("Valor de [0]: %f \n",laser_ranges[0]);
    printf("Valor de [range_size/2]: %f \n",laser_ranges[range_size/2]);
    printf("Valor de [range_max]: %f \n",range_max);
    printf("Valor de [range_min]: %f \n",range_min);
    printf("Valor de [left_side]: %f \n",left_side);
    printf("Valor de [right_side]: %f \n",right_side);

    // Check if the robot has crashed into a wall
    if (nan_count > (range_size * 0.8) || laser_ranges[range_size / 2] < 0.3) { // turtlebot: 0.25 | Uchobot: 0.30
        crashed = true;
    }
    else {
        crashed = false;
    }

    // Assign movements to a robot that still did not crash 
    if (!crashed) {
	
        if (range_min <= 0.85 && !thats_a_door) { // turtlebot: 0.5 | Uchobot: 0.1
            
	    if(laser_ranges[range_size / 2] < 0.35){
		robot_move(FORWARD)
	    }
	    else{
            following_wall = true;
            crashed = false;
            robot_move(STOP);

            if (left_side >= right_side) { // // turtlebot: left_side >= right_side | Uchobot: 0.1
                robot_move(TURN_RIGHT);
            }
            else {
                robot_move(TURN_LEFT);
            }
	    float diff = left_side-right_side;
	    printf("Valor medio: %f \n",diff);
	    //if(diff > -15.0 && diff < 50.0){robot_move(TURN_LEFT);}
	    }
        }
	/*if (right_side_lateral/100 >= 1.7) {
            following_wall = true;
            crashed = false;
            robot_move(STOP);

            if (right_side_lateral >= right_side_central) {
                robot_move(TURN_RIGHT);
            }
            else {
                robot_move(TURN_LEFT);
            }
        }
        else {
            ROS_INFO("[ROBOT] Dam son: %f , %d \n", range_max, following_wall);
            robot_move(STOP);
            if (following_wall) {
                if (range_max >= 2.1) { // turtlebot: 1.65 | Uchobot: 2.1
                    thats_a_door = true;
                    following_wall = false;
                    robot_move(TURN_RIGHT);
                    ROS_INFO("[ROBOT] I am following wall and my max range > 2.0 Range Max: %f \n", range_max);
                }
            }

            if (thats_a_door) {
                if (laser_ranges[0] <= 1.0) { // turtlebot: laser_ranges[0] <= 0.5 | Uchobot: laser_ranges[719] <= 1.0
                    thats_a_door = false;
                }
                else {
					//if(1.0 < laser_ranges[range_size/2] < 2.0){
			//	robot_move(FORWARD);//}
			//}
							//else{
                    		robot_move(GO_RIGHT);
							//}
                }
                ROS_INFO("[ROBOT] I am goin' right!: %d \n", thats_a_door);
            }
            else {
				//if (laser_ranges[0] > 1.5) {
                //    robot_move(TURN_RIGHT);
            	//}
				//else{
                robot_move(FORWARD);//}
            }
        }
    }
    // Robot should go backward since it crashed into a wall
    else {
        robot_move(BACKWARD);
    }*/
	
	float front = 0.0 , wall = 0.0;
	float door1 = 0.0 , door2 = 0.0 , door3 = 0.0, door4 = 0.0;
	for (size_t i = 0; i < range_size; i++) {
        
		if (i >= 0 && i < range_size / 8) {
            door1 += laser_ranges[i];
        }
        if (i >= range_size / 8 && i < range_size / 4) {
            door2 += laser_ranges[i];
        }
		if (i >=range_size / 4 && i < (range_size*3) / 8) {
            door3 += laser_ranges[i];
        }
		if (i >=(range_size*3) / 8 && i < range_size / 2) {
            door4 += laser_ranges[i];
        }
        }
	front = laser_ranges[range_size/2];
	wall = laser_ranges[0];
	
	if (front > 2.0){front = 2.0;}
	if (wall > 2.0){wall = 2.0;}
	
	if(wall >= 2.0){following_wall = false;}
	if(wall <= 0.4){following_wall = true;}

	printf("Range_size: %lu \n\n",range_size);
    printf("Wall: %f \n",wall);
    printf("Front: %f \n\n",front);
	printf("Door1: %f \n",door1);
	printf("Door2: %f \n",door2);
	printf("Door3: %f \n",door3);
	printf("Door4: %f \n",door4);
	//printf("Pared: %d \n\n",following_wall);
	//printf("Pared: %s \n\n",following_wall ? "true" : "false");

	if( std::isinf(door1) && std::isinf(door3) ){
		printf("Puerta abiertaaaaaaa\n\n");
		thats_a_door = true;
		robot_move(GO_LEFT);
		if(front < 2.0){robot_move(FORWARD);} // Un Puente
		if(front > 2.0){robot_move(GO_RIGHT);} // Un salvavidas
	}

	if( !(std::isinf(door1) && std::isinf(door3)) ){
		thats_a_door = false;
		//robot_move(STOP);

	}

	if(!following_wall && !thats_a_door){
	printf("Pared: false \n\n");
		if(wall > front){
			if(front > 0.3 && front < 1.2){robot_move(FORWARD);}
			else{robot_move(TURN_LEFT);}	
		}
		if(wall == front){
			printf("\nEsquina abierta \n\n");
			robot_move(TURN_RIGHT);
		}
	}

	if(following_wall && !thats_a_door){
	printf("Pared: true \n\n");
		if(front > 0.3){
			if(wall < 0.3){robot_move(TURN_LEFT);}
			if(wall > 0.3 && wall < 0.5){robot_move(FORWARD);}
			if(wall > 0.5){robot_move(TURN_RIGHT);}
		}
		if(front <= 0.3){robot_move(TURN_LEFT);}
		if(front <= 0.1){robot_move(BACKWARD);}
	}

}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "wall_follower");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 100
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/teleop/cmd_vel", 100); // To Ucho Bot
    //motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 100); // To Turtlebot

    // Subscribe to the /scan topic and call the laser_callback function
    laser_subscriber = n.subscribe("/udacity_map/laser/scan", 1000, laser_callback); // To Ucho Bot
    //laser_subscriber = n.subscribe("/scan", 1000, laser_callback); // To Turtlebot

    // Enter an infinite loop where the laser_callback function will be called when new laser messages arrive
    ros::Duration time_between_ros_wakeups(0.001);
    while (ros::ok()) {
        ros::spinOnce();
        time_between_ros_wakeups.sleep();
    }

    return 0;
}
