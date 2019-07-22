#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <iostream>

#include <dynamixel_controller_msg/MotorStateMsg.h>
#include "dynamixel_controller_msg/StateEnableMsg.h"
#include <boost/thread/thread.hpp>

int _tick7 = 0;
int _tick8 = 0;
int tick7 = 0;
int tick8 = 0;
ros::Time current_time_encoder, last_time_encoder;
const double radius = 0.045;
const double distwheels = 0.166;
const double numTicks = 4096.0;
const double pi = 3.14159265;
double distancePerTick = radius * (2 * pi / numTicks);
double radPerTick = 0.088 * pi / 180;

double x = 0.0;
double y = 0.0;
double th = 0.0;

//double vx = 0.0;
//double vy = 0.0;
//double vth = 0.0;
double deltaLeft = 0.0;
double deltaRight = 0.0;

//double dx = 0.0;
//double dy = 0.0;
//double dth = 0.0;
bool first = true;


void MotorStateCallback(const dynamixel_controller_msg::MotorStateMsg& msg) {
    if ((msg.present_speed[6] != 0 && msg.Moving[6] == 1)
               || (msg.present_speed[7] != 0 && msg.Moving[7] == 1)) {
	if (first) {
        tick7 = msg.present_position[6];
        tick8 = msg.present_position[7];
		_tick7 = tick7;
		_tick8 = tick8;
		current_time_encoder = ros::Time::now();
		last_time_encoder = current_time_encoder;
		first = false;
	} else {
        tick7 = msg.present_position[6];
        tick8 = msg.present_position[7];
		current_time_encoder = ros::Time::now();
	}
    }   
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "odometry_publisher");
    ros::NodeHandle n;
    ros::NodeHandlePtr node = boost::make_shared<ros::NodeHandle>();
    ros::Publisher state_enable_pub = n.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);
    ros::Subscriber mode_ctrl_sub = node->subscribe("Motor_state", 100, &MotorStateCallback);
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
    tf::TransformBroadcaster odom_broadcaster;

    dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    state_enable_msg.enable = 0;

    ros::Time current_time;
    current_time = ros::Time::now();

    ros::Rate r(10);
    while(n.ok()) {//n.ok()

        state_enable_pub.publish(state_enable_msg); 

	ros::spinOnce();
        current_time = ros::Time::now();

	//double R = distwheels / 2.0 * (v_left + v_right) / (v_right - v_left);

	double deltaTick7 = tick7 - _tick7;
	double deltaTick8 = tick8 - _tick8;
	double dt = (current_time_encoder - last_time_encoder).toSec();

	double v_left = 0;
	double v_right = 0;
	if (dt != 0) {
		v_left = deltaTick7 * radPerTick * radius / dt;
		v_right = (-1.0) * deltaTick8 * radPerTick * radius / dt;
	}

	double v_avg = (v_left + v_right) / 2.0;
	//printf("%f \n", dt);
	double s = v_avg * dt;
	double vth = (v_right - v_left) / distwheels;
	double dth = vth * dt;

	th += dth;

	//double delta_x = (v_left * cos(th) - v_right * sin(th)) * dt_encoder;
	double delta_x = s * cos(th + (dth / 2.0));
	//double delta_y = (v_left * sin(th) + v_right * cos(th)) * dt_encoder;
	double delta_y = s * sin(th + (dth / 2.0));
	double vx = 0;
	double vy = 0;
	if (dt != 0) {
		vx = delta_x / dt;
		vy = delta_y / dt;
	}
	x += delta_x;
	y += delta_y;
	
/////////////////////////////////////////////////////////////////////////////////////////////////	
        geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_link";

        odom_trans.transform.translation.x = x;
        odom_trans.transform.translation.y = y;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        //send the transform
        odom_broadcaster.sendTransform(odom_trans);

        //Odometry message
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "odom";

        //set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = odom_quat;

         //set the velocity
        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;

        //publish the message
        odom_pub.publish(odom);
	
        r.sleep();

	last_time_encoder = current_time_encoder;
	_tick7 = tick7;
	_tick8 = tick8;
        //first = true;
        //printf("outside loop time2 = %f\n", ros::Time::now().toSec());
      }

}
