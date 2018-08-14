
# Deep RL Arm Manipulation

This project is based on the Nvidia open source project "jetson-reinforcement" developed by [Dustin Franklin](https://github.com/dusty-nv). The goal of the project is to create a DQN agent and define reward functions to teach a robotic arm to carry out two primary objectives:

1. Have any part of the robot arm touch the object of interest, with at least a 90% accuracy.
2. Have only the gripper base of the robot arm touch the object, with at least a 80% accuracy.

## Building from Source (Nvidia Jetson TX2)

Run the following commands from terminal to build the project from source:

``` bash
$ sudo apt-get install cmake
$ git clone http://github.com/udacity/RoboND-DeepRL-Project
$ cd RoboND-DeepRL-Project
$ git submodule update --init
$ mkdir build
$ cd build
$ cmake ../
$ make
```

During the `cmake` step, Torch will be installed so it can take awhile. It will download packages and ask you for your `sudo` password during the install.

## Testing the API

To make sure that the reinforcement learners are still functioning properly from C++, a simple example of using the API called [`catch`](samples/catch/catch.cpp) is provided.  Similar in concept to pong, a ball drops from the top of the screen which the agent must catch before the ball reaches the bottom of the screen, by moving it's paddle left or right.

To test the textual [`catch`](samples/catch/catch.cpp) sample, run the following executable from the terminal.  After around 100 episodes or so, the agent should start winning the episodes nearly 100% of the time:  

<img src="https://github.com/Miguelucho/RoboND-DeepRL-Project/blob/master/img/catch/Captura%20de%20pantalla%20de%202018-07-25%2004-28-29.jpg">
<img src="https://github.com/Miguelucho/RoboND-DeepRL-Project/blob/master/img/catch/Captura%20de%20pantalla%20de%202018-07-25%2004-32-48.jpg">

Internally, [`catch`](samples/catch/catch.cpp) is using the [`dqnAgent`](c/dqnAgent.h) API from our C++ library to implement the learning.


## Project Environment

To get started with the project environment, run the following:

``` bash
$ cd RoboND-DeepRL-Project/build/aarch64/bin
$ chmod u+x gazebo-arm.sh
$ ./gazebo-arm.sh
```
<img src="https://github.com/Miguelucho/RoboND-DeepRL-Project/blob/master/img/80%25/Captura%20de%20pantalla%20de%202018-07-26%2021-17-02.jpg">

The plugins which hook the learning into the simulation are located in the `gazebo/` directory of the repo. The RL agent and the reward functions are to be defined in [`ArmPlugin.cpp`](gazebo/ArmPlugin.cpp).
