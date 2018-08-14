#!/bin/sh

export TURTLEBOT_3D_SENSOR=kinect
xterm -e " roslaunch official_ros turtlebot_world.launch world_file:=/home/nvidia/workspaceROS/RoboND-HomeServiceRobot/catkin_ws/src/world/world_u.world " &  
sleep 8
xterm -e " roslaunch official_ros gmapping_mode.launch " & 
sleep 8
xterm -e " roslaunch official_ros view_navigation.launch " &
sleep 8
xterm -e " rosrun wall_follower wall_follower"
