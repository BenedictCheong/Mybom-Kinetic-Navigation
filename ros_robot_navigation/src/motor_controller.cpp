#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/MotorControlMsg.h>
#include "dynamixel_controller_msg/StateEnableMsg.h"
//#include <dynamixel_controller_msg/TorqueMsg.h>
#include <geometry_msgs/Twist.h>
#include <ros_robot_navigation/msgCommand2.h>



#include <boost/thread/thread.hpp>

double vel_x = 0;
double vel_th = 0;
const double l = 0.166;
const double pi = 3.141592;

ros::Publisher msg_command_pub2;

int flagi = 0;

void motor_move(const geometry_msgs::Twist::ConstPtr& msg)
{
	vel_x = msg->linear.x;
	vel_th = msg->angular.z;
	flagi = 1;
	ros_robot_navigation::msgCommand2 msg_;
	if (vel_x == 0 && vel_th == 0){
		msg_.command_switch = false;
	}
	else
	{
		msg_.command_switch = true;
	}
	msg_command_pub2.publish(msg_);
}
int main(int argc, char** argv) {

	ros::init(argc, argv, "motor_controller");
	ros::NodeHandle nh;


	//ros::Publisher motor_ctrl_pub, torque_ctrl_pub, state_enable_pub;
        ros::Publisher motor_ctrl_pub, state_enable_pub;

	//motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
	motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
	//torque_ctrl_pub = nh.advertise<dynamixel_controller_msg::TorqueMsg>("torque", 100);
	state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);

	ros::Subscriber cmd_vel_sub = nh.subscribe("cmd_vel",100,motor_move);
	msg_command_pub2 = nh.advertise<ros_robot_navigation::msgCommand2>("msgCommand_cmdvel", 100);


	//dynamixel_controller_msg::TorqueMsg torque_msg;
	dynamixel_controller_msg::StateEnableMsg state_enable_msg;
	//torque_msg.torque = true;
	state_enable_msg.enable = 1;
	ros::Duration(0.5).sleep();

	//torque_ctrl_pub.publish(torque_msg);
	//state_enable_pub.publish(state_enable_msg);
	int sampling_freq = 10;
	ros::Rate loop_rate(sampling_freq);

	while(ros::ok()){

	    //state_enable_pub.publish(state_enable_msg);

	    std::vector<uint32_t> ids;
	    std::vector<uint32_t> positions;
	    std::vector<int32_t> velocities;



	    if(flagi == 1){


		ids.push_back(7);
		ids.push_back(8);

		double scale = 800;
		//double right_vel = -1.0 * (vel_x + vel_th * (l / 2.0));
		//double left_vel = vel_x - vel_th * (l / 2.0);
		double right_vel = -1.0 * (vel_x + vel_th * (l / 2.0));
		double left_vel = vel_x - vel_th * (l / 2.0);
		
		/*if(vel_x == 0){
		    right_vel = vel_th * 0.166 / 2.0 * scale;
		    if (vel_th >= 0) {
		        right_vel += 1024;
		    } else {
		        right_vel *= -1.0;
		    }
		    left_vel = right_vel;
		}
		else if(vel_th == 0){
		    left_vel = vel_x * scale;
		    if (left_vel < 0) {
		        left_vel *= -1.0;
		    }
		    right_vel = left_vel + 1024;
		}

		else{
		    left_vel = (vel_x - vel_th / 2.0)*scale;
		    right_vel = (vel_x + vel_th / 2.0)*scale + 1024;
		}*/
		left_vel *= scale;
		right_vel *= scale;
	/*
		if (right_vel < 0) {
		    right_vel *= -1.0;
		    right_vel += 1024;
		}
		if (left_vel < 0) {
		    left_vel *= -1.0;
		    left_vel += 1024;
		}
	*/

		velocities.push_back(left_vel);
		velocities.push_back(right_vel);

		dynamixel_controller_msg::MotorControlMsg msg;
		msg.motor_ids = ids;
		msg.positions = positions;
		msg.velocities = velocities;

		motor_ctrl_pub.publish(msg);
		flagi = 0;

	    }

	    ros::spinOnce();
		loop_rate.sleep();
	}
   
}
