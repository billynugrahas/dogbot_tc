
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <assert.h>
#include <functional>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "dogbot/DogBotAPI.hh"
#include "dogbot/DogBotControllerROS.hh"
#include "dogbot/SplineGaitController.hh"

int main(int argc, char **argv) {
  ros::init(argc, argv, "dogbot_simplegait");
  ros::NodeHandle n;
  ros::NodeHandle nPrivate("~");

  std::string robotns = "dogbot";
  nPrivate.getParam("robot", robotns);

  float loopHz = 100;
  float omega = 0.5;
  std::string robot_config_file = "~/robot_config/robot.json";
  nPrivate.getParam("loop_hz", loopHz);
  nPrivate.getParam("omega", omega);
  nPrivate.getParam("robot_config_file", robot_config_file);

  ROS_WARN("[loop_hz,omega]=[%f,%f], robot_config_file=%s, robotns=%s", loopHz,
           omega, robot_config_file.c_str(), robotns.c_str());

  ros::AsyncSpinner spinner(2);

  sensor_msgs::JointState::ConstPtr lastJointState;

  std::shared_ptr<DogBotN::DogBotKinematicsC> dogBotKinematics =
      std::make_shared<DogBotN::DogBotKinematicsC>();

  if (!dogBotKinematics->LoadConfig(robot_config_file)) {
    std::cerr << "Failed to load robot config. " << std::endl;
  }

  DogBotN::DogBotControllerROSC legs(robotns, dogBotKinematics);

  sleep(3);

  float updatePeriod = 1.0f / loopHz;
  legs.SetupTrajectory(updatePeriod, 15);

  DogBotN::SplineGaitControllerC gaitGenerator;
  gaitGenerator.SetOmega(omega);

  std::cout << "Starting controller. Updated.  LoopHz:" << loopHz
            << " Omega:" << omega << std::endl;

  ros::Timer timer1 = n.createTimer(
      ros::Duration(updatePeriod),
      [&legs, &gaitGenerator, updatePeriod](const ros::TimerEvent &te) {
        //! Do a single timestep
        // std::cout << "Update. " << std::endl;
        DogBotN::SimpleQuadrupedPoseC pose;
        gaitGenerator.Step(updatePeriod, pose);
        legs.NextTrajectory(pose);
      });

  // Wait until shutdown signal received
  spinner.start();
  ros::waitForShutdown();

  std::cout << "Done " << std::endl;

  return 0;
}
