#!/bin/sh

export TURTLEBOT_3D_SENSOR=kinect
xterm -e " roslaunch official_ros turtlebot_world.launch world_file:=/home/nvidia/workspaceROS/RoboND-HomeServiceRobot/catkin_ws/src/world/world_u.world " & 
sleep 5
xterm -e " roslaunch official_ros amcl_mode.launch " &
sleep 5
xterm -e " roslaunch official_ros view_navigation.launch " &
sleep 5
xterm -e " rosrun add_markers add_markers " &
sleep 5
xterm -e " rosrun pick_objects pick_objects "
