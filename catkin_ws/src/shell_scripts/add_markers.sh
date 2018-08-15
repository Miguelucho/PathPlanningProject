#!/bin/sh

export TURTLEBOT_3D_SENSOR=kinect
xterm -e " roslaunch official_ros turtlebot_world.launch world_file:=/home/nvidia/workspaceROS/RoboND-HomeServiceRobot/catkin_ws/src/world/world_u.world " & 
sleep 5
xterm -e " roslaunch official_ros amcl_mode.launch map_file:=/home/nvidia/workspaceROS/RoboND-HomeServiceRobot/catkin_ws/src/world/maps/map_u.yaml 3d_sensor:=kinect" &
sleep 5
xterm -e " roslaunch official_ros view_navigation.launch " &
sleep 5
xterm -e " rosrun add_markers add_markers "
