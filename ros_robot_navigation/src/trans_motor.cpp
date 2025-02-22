#include "ros/ros.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/ModeControlMsg.h>
#include "dynamixel_controller_msg/MotorControlMsg.h"
//#include <dynamixel_controller_msg/TorqueMsg.h>
#include "dynamixel_controller_msg/StateEnableMsg.h"

#include <boost/thread/thread.hpp>


#include <tf/transform_listener.h>

const double pi = 3.14159265;
const double numTicks = 4096;
const double radius = 0.045;
const double d = 0.166;
const double max_coeff = 60;
const double unit_rps = 0.0019;
double distancePerTick= radius * (2 * pi / numTicks);


void hold(double sec) {
    //int count = 0;
    //ros::Rate r(1);
    ros::Duration(sec).sleep();
    /*while (ros::ok() && (count <= sec)) {
		r.sleep();
		count++;
    }*/
}
std::vector<int> forward(double dist) {
	int coeff_right = max_coeff + 1024;
	int coeff_left = max_coeff;
	std::vector<int> velocities;
	velocities.push_back(coeff_left);
	velocities.push_back(coeff_right);
	return velocities;
}
std::vector<int> rotation(double ang) {
	int coeff_right = 0;
	int coeff_left = 0;
	if (ang > 0) {
		coeff_right = max_coeff + 1024;
		coeff_left = max_coeff + 1024;
    } else if (ang < 0){
		coeff_right = max_coeff;
        coeff_left = max_coeff;
	}
    std::cout<<"coeffs: "<<coeff_left << "and" << coeff_right<<std::endl;
	std::vector<int> velocities;
	velocities.push_back(coeff_left);
	velocities.push_back(coeff_right);
	return velocities;
}
std::vector<int> stop(void) {
	std::vector<int> velocities;
	velocities.push_back(0);
	velocities.push_back(0);
	return velocities;
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "trans_motor");
    ros::NodeHandle nh;

    std::vector<uint32_t> ids;
    ids.push_back(7);
    ids.push_back(8);

    ros::Publisher state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_enable", 100);
    dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    state_enable_msg.enable = 1;
    state_enable_pub.publish(state_enable_msg);


    //double coeff_left = 0;
    //double coeff_right = 0;
    
    double actual_rps = unit_rps * max_coeff;
    double max_actual_speed = actual_rps * radius;


    double x = 0.1;
    double y = 0.0;
    double theta = 0;
    if (x == 0 && y != 0) {
		theta = pi / 2;
    } else {
        atan(y/x);
    }
    double ang_z = pi;
    double dist = sqrt(x*x + y*y);
    
    double hold_time = 0;
    double circumGo = 0;
    
    //ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    //ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
    ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    //ros::Publisher mode_pub = nh.advertise<dynamixel_controller_msg::ModeControlMsg>("Mode", 100);
    //ros::Publisher Torque_pub=nh.advertise<dynamixel_controller_msg::TorqueMsg>("torque", 100);

    //dynamixel_controller_msg::TorqueMsg torque_msg;
    //torque_msg.torque = true;
    //Torque_pub.publish(torque_msg);
    //ros::Duration(0.5).sleep();
    dynamixel_controller_msg::MotorControlMsg msg;
    msg.motor_ids = ids;

    //ros::Rate r(5);

	bool rotation_enabler = false;
	bool forward_enabler = false;
    bool angleCompensator_enabler = false;
	
    if (dist != 0) forward_enabler = true;
//    if (theta != 0)	rotation_enabler = true;
//    if ((theta - ang_z) != 0) angleCompensator_enabler = true;
    hold(0.5);
	if (rotation_enabler) {
        std::cout<<"rotation\n"<<std::endl;
        circumGo = d / 2.0 * theta;
        //std::cout<<"rot_d = "<< d <<std::endl;
        //std::cout<<"rot_circumgo = "<< circumGo <<std::endl;
        //std::cout<<"rot_theta = "<< theta <<std::endl;
		hold_time = circumGo / max_actual_speed;
        std::cout<<"rot_holdtime = "<< hold_time <<std::endl;
        if (hold_time < 0) hold_time*=-1;
        msg.velocities = rotation(0);
        motor_ctrl_pub.publish(msg);
        hold(hold_time);
        msg.velocities = stop();
        motor_ctrl_pub.publish(msg);
	}
    hold(0.5);
	if (forward_enabler) {
        std::cout<<"forward\n"<<std::endl;
		hold_time = dist / max_actual_speed;
         std::cout<<"fw dist = "<< dist <<std::endl;
         std::cout<<"fw max spped = "<< max_actual_speed <<std::endl;
        std::cout<<"fw holdtime = "<< hold_time <<std::endl;
		msg.velocities = forward(dist);
		motor_ctrl_pub.publish(msg);
		hold(hold_time);
		msg.velocities = stop();
		motor_ctrl_pub.publish(msg);
	}
    hold(0.5);
	if (angleCompensator_enabler) {
        std::cout<<"compensator\n"<<std::endl;
		double compensated_angle = ang_z - theta;
        circumGo = d / 2.0 * compensated_angle;
		hold_time = circumGo / max_actual_speed;
        if (hold_time < 0) hold_time*=-1;
        //std::cout<<"cmp oldtime = "<< hold_time <<std::endl;
        //std::cout<<"cmp angle = "<<compensated_angle<<std::endl;
		msg.velocities = rotation(compensated_angle);
		motor_ctrl_pub.publish(msg);
		hold(hold_time);
		msg.velocities = stop();
		motor_ctrl_pub.publish(msg);
	}
    hold(0.5);
	
    //ros::spin();
    //r.sleep();
    ros::shutdown();
	return 0;
}
