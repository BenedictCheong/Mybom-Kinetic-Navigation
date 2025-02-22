#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/MotorControlMsg.h>
#include "dynamixel_controller_msg/StateEnableMsg.h"

#include <ros_robot_controller/msgTutorial.h>
#include <ros_robot_controller/RemsgTutorial.h>

#include <boost/thread/thread.hpp>


ros::Publisher state_enable_pub;
ros::Publisher motor_ctrl_pub;
ros::Publisher motor_Reinterface_pub;


int main(int argc, char** argv) {

    ros::init(argc, argv, "action_motor");
    ros::NodeHandle nh;

    //state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_enable", 100);
    state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);
    //motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("Motor_ctrl", 100);
    //motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
    motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    motor_Reinterface_pub = nh.advertise<ros_robot_controller::RemsgTutorial>("RemsgTutorial_value", 100);

    dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    state_enable_msg.enable = 0;

    int sampling_freq = 100;
    ros::Rate loop_rate(sampling_freq);

//    std::cout << "w1" << std::endl;
    dynamixel_controller_msg::MotorControlMsg msg;
    ros_robot_controller::RemsgTutorial msg2_;
    std::vector<uint32_t> ids;
    ids.push_back(7);
    ids.push_back(8);
    int count=0;
    while (ros::ok())
    {
	state_enable_pub.publish(state_enable_msg);
	std::vector<int32_t> velocities;
        if(count<500)
	{
	    velocities.push_back(160);
            velocities.push_back(160);
	}
	else
	{
	    velocities.push_back(-160);
            velocities.push_back(-160);
	}
        msg.motor_ids = ids;
        msg.velocities = velocities;
        motor_ctrl_pub.publish(msg);
        if(count==1000)
	{
	    count=0;
	}
	else
	{
	    count++;
	}
        ros::spinOnce();
        loop_rate.sleep();

    }
    printf("a");
    std::vector<int32_t> velocities;
    velocities.push_back(0);
    velocities.push_back(0);
    msg.motor_ids = ids;
    msg.velocities = velocities;
    motor_ctrl_pub.publish(msg);

    
    return 0;
}
