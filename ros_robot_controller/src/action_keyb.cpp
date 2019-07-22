#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <termios.h>
#include <stdio.h>
//#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/MotorControlMsg.h>
//#include "dynamixel_controller_msg/StateEnableMsg.h"
//#include <dynamixel_controller_msg/TorqueMsg.h>
#include <ros_robot_controller/msgCommand.h>

#include <boost/thread/thread.hpp>

int vel_left = 0;
int vel_right = 0;

//ros::Publisher torque_ctrl_pub;
//ros::Publisher state_enable_pub;
ros::Publisher motor_ctrl_pub;
ros::Publisher msg_command_pub;

int getch(void);
#define ESC_ASCII_VALUE    0x1b
#define FORWARD            0x77
#define BACKWARD           0x78
#define LEFT               0x61
#define RIGHT              0x64
#define STOPS              0x73

int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  //std::cout<< c <<std::endl;

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "action_keyb");
    ROS_INFO("Set angular velocity(+-0.2rad/sec) to your motor!! by using keyboard");
    ROS_INFO("w : Forward");
    ROS_INFO("x : Backward");
    ROS_INFO("a : Left");
    ROS_INFO("d : Right");
    ROS_INFO("s : STOPS\n");
    ROS_INFO("ESC : exit");

    ros::NodeHandle nh;

    //ros::Subscriber motor_value_sub = nh.subscribe("Motor_value",10,msgCallback_value);
    //torque_ctrl_pub = nh.advertise<dynamixel_controller_msg::TorqueMsg>("torque", 100);
    //state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_enable", 100);
    //motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("Motor_ctrl", 100);
    motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    //ros::Subscriber motor_state_sub = nh.subscribe("Motor_state",10,msgCallback);
    //motor_Reinterface_pub = nh.advertise<ros_robot_controller::RemsgTutorial>("RemsgTutorial_value", 100);
    msg_command_pub = nh.advertise<ros_robot_controller::msgCommand>("msgCommand_keyb", 100);

    //dynamixel_controller_msg::TorqueMsg torque_msg;
    //dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    //torque_msg.torque = true;
    //state_enable_msg.enable = 1;
    ros::Duration(0.5).sleep();
    //torque_ctrl_pub.publish(torque_msg);
    //state_enable_pub.publish(state_enable_msg);

    int sampling_freq = 5;
    ros::Rate loop_rate(sampling_freq);

    dynamixel_controller_msg::MotorControlMsg msg;
    //ros_robot_controller::RemsgTutorial Remsg;
    ros_robot_controller::msgCommand msg_;

    while (ros::ok())
    {
        std::vector<uint32_t> ids;
        std::vector<uint32_t> positions;
        std::vector<int32_t> velocities;

        ids.push_back(7);
        ids.push_back(8);

	char c = getch();
	//std::cout<< c <<std::endl;

	if (c == ESC_ASCII_VALUE)
	{
		std::cout<< "ESC_ASCII_VALUE" <<std::endl;
		vel_left = 0.0;
		vel_right = 0.0;
		msg_.command_switch = false;
		velocities.push_back(vel_left);
		velocities.push_back(vel_right);
		msg.motor_ids = ids;
		msg.velocities = velocities;
		motor_ctrl_pub.publish(msg);
		ros::shutdown();
		//break;
	}
	if (c == FORWARD)
	{
		std::cout<< "FORWARD" <<std::endl;
		vel_left += 0.2*84;
		vel_right -= 0.2*84;
		msg_.command_switch = true;
	}
	else if (c == BACKWARD)
	{
		std::cout<< "BACKWARD" <<std::endl;
		vel_left -= 0.2*84;
		vel_right += 0.2*84;
		msg_.command_switch = true;
	}
	else if (c == LEFT)
	{
		std::cout<< "LEFT" <<std::endl;
		vel_left -= 0.2*84;
		vel_right -= 0.2*84;
		msg_.command_switch = true;
	}
	else if (c == RIGHT)
	{
		std::cout<< "RIGHT" <<std::endl;
		vel_left += 0.2*84;
		vel_right += 0.2*84;
		msg_.command_switch = true;
	}
	else if (c == STOPS)
	{
		std::cout<< "STOPS" <<std::endl;
		vel_left = 0.0;
		vel_right = 0.0;
		msg_.command_switch = false;
	}

	   std::cout<< "vel_left:  " << vel_left <<std::endl;
	   std::cout<< "vel_right: " << vel_right <<std::endl;
           velocities.push_back(vel_left);
           velocities.push_back(vel_right);

           msg.motor_ids = ids;
           //msg.positions = positions;
           msg.velocities = velocities;

           motor_ctrl_pub.publish(msg);
	   msg_command_pub.publish(msg_);


        ros::spinOnce();
        loop_rate.sleep();


    }

    ros::spin();

    return 0;
}
