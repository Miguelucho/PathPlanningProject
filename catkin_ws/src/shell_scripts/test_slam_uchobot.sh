#!/bin/sh

#export TURTLEBOT_3D_SENSOR=kinect
xterm -e " roslaunch owner_pkg world.launch " &  
sleep 8
xterm -e " roslaunch owner_pkg mapping.launch " & 
sleep 8
xterm -e " roslaunch owner_pkg rviz.launch " &
sleep 8
xterm -e " roslaunch owner_pkg teleop.launch "
