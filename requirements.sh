#!/usr/bin/env bash

sudo apt-get update

sudo apt-get install libspdlog-dev -y
sudo apt-get install jsoncpp-dev -y
sudo apt-get install libeigen3-dev -y
sudo apt-get install libzmq-dev -y
sudo apt-get install libzmq3-dev -y
sudo apt-get install libusb-1.0.0-dev -y
sudo apt-get install mesa-common-dev -y
sudo apt-get install build-essential -y
sudo apt-get install libgl1-mesa-dev -y
sudo apt-get install libpqxx-dev -y

sudo apt-get install ros-kinetic-rosparam-shortcuts -y
sudo apt-get install ros-kinetic-ros-control -y
sudo apt-get install ros-kinetic-ros-controllers -y
sudo apt-get install ros-kinetic-pluginlib -y

#cd ~/dogbot2_ws/src/DogBotSoftware/Scripts/

#NAME_OF_DOG="hachiko"
#./setup.sh $NAME_OF_DOG 1

# To avoid this error:
# Building ROS packages with catkin build
# /home/rdaneel/ros_playground/dogbot2_ws/src/DogBotSoftware/Scripts/rosbuild.sh: line 9: catkin: command not found
# We have to modify the rosbuild.sh

# We create our own config file
#cp ~/ros_playground/dogbot2_ws/src/DogBotSoftware/Config/tango.json ~/ros_playground/dogbot2_ws/src/DogBotSoftware/Config/$NAME_OF_DOG.json
#ll ~/.config/dogbot/robot.json
#--> It should point to your file
