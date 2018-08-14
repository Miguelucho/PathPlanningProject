
# Home Service Robot

The main objective of this project is that a robot (bot) can plan the route from point A to point B and that the bot can avoid obstacles on the way. To achieve the main objective, the project is divided into smaller objectives that are detailed below:

1. Design a simple environment with the Building Editor in Gazebo.
2. Teleoperate your robot and manually test SLAM.
3. Create a wall_follower node that autonomously drives your robot to map your environment.
4. Use the ROS navigation stack and manually commands your robot using the 2D Nav Goal arrow in rviz to move to 2 different desired positions and orientations.
5. Write a pick_objects node that commands your robot to move to the desired pickup and drop off zones.
6. Write an add_markers node that subscribes to your robot odometry, keeps track of your robot pose, and publishes markers to rviz.

For each mini target, a shell file was created that contains the nodes and launchers necessary to fulfill the objective.

**Important:** One part of the project uses ROS packages and the others part are their own packages. Although the ROS packages are already contained in this repository, it is described below how to obtain them.

### Building from Source (Nvidia Jetson TX2)

Run the following commands from terminal to build the project from source:

```bash
$ sudo apt-get install xterm
$ sudo apt-get update
$ sudo apt-get install ros-kinetic-navigation
```
The ROS packages were obtained from the following repositories:

https://github.com/ros-perception/slam_gmapping.git  
https://github.com/turtlebot/turtlebot.git  
https://github.com/turtlebot/turtlebot_interactions.git  
https://github.com/turtlebot/turtlebot_simulator.git  

continuing with the construction of the project:

```bash
$ git clone https://github.com/Miguelucho/PathPlanningProject.git
$ cd ~/PathPlanningProjectcd/catkin_ws/src
$ catkin_init_workspace
$  cd ~/catkin_ws
$ catkin_make
 ...  [ Wait ] ...
$ source devel/setup.bash
READY
```
The project is completely developed with the Gazebo bot named turtlebot. But at the moment I am developing this project with a bot and an environment that I built. I built a bot named Uchobot, which is larger, with sensors in front of the wheels and more complex sensors than the ROS bot (Turtlebot). I also contributed a mini maze more complex than a simple U. Both elements added a significant number of new challenges and challenges for the project.

Quickly: "The new environment has a door at the end and only this detail a little complicated the code."

![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/2Bots.png)

### Mini Targets

##### Test SLAM.
```bash
$ cd ~/src/shell_scripts
$ ./test_slam.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/Captura%20de%20pantalla%20de%202018-08-13%2018-31-36.jpg)

##### Wall Follower.
```bash
$ cd ~/src/shell_scripts
$ ./wall_follower.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/Captura%20de%20pantalla%20de%202018-08-11%2020-42-38.jpg)

##### Test Navigation.
```bash
$ cd ~/src/shell_scripts
$ ./test_navigation.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/Captura%20de%20pantalla%20de%202018-08-13%2020-12-48.jpg)

##### Reach Multiple Goals.
```bash
$ cd ~/src/shell_scripts
$ ./pick_objects.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/Captura%20de%20pantalla%20de%202018-08-14%2010-44-54.jpg)

##### Model Virtual Objects.
```bash
$ cd ~/src/shell_scripts
$ ./add_markers.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/Captura%20de%20pantalla%20de%202018-08-14%2011-45-55.jpg)

##### All Together [Home Service Robot].
```bash
$ cd ~/src/shell_scripts
$ ./home_service.sh
```
![alt text](https://github.com/Miguelucho/PathPlanningProject/blob/master/catkin_ws/img/c548213d54d.gif)
