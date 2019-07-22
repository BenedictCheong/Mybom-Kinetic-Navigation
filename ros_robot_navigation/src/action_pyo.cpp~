#include "ros/ros.h"
//#include <iostream>
#include <vector>
//#include <stdio.h>
#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/MotorControlMsg.h>
#include "dynamixel_controller_msg/StateEnableMsg.h"
//#include <dynamixel_controller_msg/TorqueMsg.h>

#include <action_execution_msgs/Package.h>
#include <action_execution_msgs/Command_result.h>

#include <boost/thread/thread.hpp>


int method[4];//1:forward, 2:backward, 3:left_turn, 4:right_turn, 0:stop
int goal_velocities[4];
int distance_rotate[4];
/*
int _tick7 = 0;
int _tick8 = 0;
int tick7 = 0;
int tick8 = 0;
ros::Time current_time_encoder, last_time_encoder;
const double radius = 0.045;
const double distwheels = 0.166;
const double numTicks = 4096.0;
const double pi = 3.14159265;
double distancePerTick= radius * (2 * pi / numTicks);
*/
//int method[] = {3,0,1,0,4,0};//1:forward, 2:backward, 3:left_turn, 4:right_turn, 0:stop
//int method[] = {3,1,4,0};//1:forward, 2:backward, 3:left_turn, 4:right_turn, 0:stop
//int goal_velocities[] = {1, 3, 1, 0};
//int distance_rotate[] = {180, 180, 180, 0};
//int method[] = {1, 0};//1:forward, 2:backward, 3:left_turn, 4:right_turn, 0:stop
//int goal_velocities[] = {1, 0};
//int distance_rotate[] = {180, 0};
int i = 0;
int vel_raw;
int vel_left = 0;
int vel_right = 0;
const double pi = 3.14159265;

int total_action;

int start_position_left;
int start_position_right;
int var_odo_left;
int var_odo_right;
int preposition_left;
int preposition_right;
int flag1 = 1;
int flag2 = 1;
int flag3 = 1;
int dist = 0;

//int flag6 = 1;
int flag7 = 1;
bool stop = false;

void msgCallback(const dynamixel_controller_msg::MotorStateMsg::ConstPtr& msg)
{
//    ROS_INFO("7: %d   8: %d", msg->present_position[0], (msg->present_position[1]*(-1)));
    preposition_left = msg->present_position[0];
    preposition_right = msg->present_position[1]*(-1);
    while(flag1){start_position_left = preposition_left;flag1 = 0;}
    while(flag2){start_position_right = preposition_right;flag2 = 0;}
//    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
    var_odo_left = abs(preposition_left - start_position_left);
    var_odo_right = abs(preposition_right - start_position_right);
    if (method[i]==3 || method[i]==4)//turn
    {
        //dist = (int(abs(distance_rotate[i]*0.14*140))-int(goal_velocities[i]*10.47125));
        dist = int(abs(distance_rotate[i]*0.14*140));
    }
    if (method[i]==1 || method[i]==2)//turn
    {
        //dist = (int(abs(distance_rotate[i]*144.8664))-int(goal_velocities[i]*10.47125));
        dist = int(abs(distance_rotate[i]*144.8664));
    }
    if ((var_odo_left*0.5+var_odo_right*0.5)>=dist)
    {
        ros::NodeHandle nh_;
        //ros::Publisher motor_ctrl_pub_ = nh_.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
	ros::Publisher motor_ctrl_pub_ = nh_.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_controll", 100);
        ros::Publisher Command_result_pub_ = nh_.advertise<action_execution_msgs::Command_result>("CommandResult", 100);
        dynamixel_controller_msg::MotorControlMsg msg_;
        action_execution_msgs::Command_result msg2_;
        std::vector<uint32_t> ids_;
        std::vector<uint32_t> positions_;
        std::vector<int32_t> velocities_;
/*
        i = i + 1;
        flag1 = 1;
        flag2 = 1;
        flag3 = 1;
        flag6 = 1;
        flag7 = 1;
*/
        ids_.push_back(7);
        ids_.push_back(8);
        velocities_.push_back(0);
        velocities_.push_back(1024);
        msg_.motor_ids = ids_;
        msg_.positions = positions_;
        msg_.velocities = velocities_;

        motor_ctrl_pub_.publish(msg_);

        if (stop)
        {
            /*
            msg2_.id = 78;
            msg2_.package_name = "ros_robot_navigation";
            msg2_.success = true;
            msg2_.error_id = 100;
            std::cout<< msg2_.id <<std::endl;
            std::cout<< msg2_.package_name <<std::endl;
            std::cout<< msg2_.success <<std::endl;
            std::cout<< msg2_.error_id <<std::endl;
            Command_result_pub_.publish(msg2_);
            */
            std::cout<<"msg2_"<<std::endl;
        }
        else
        {
            i = i + 1;
            flag1 = 1;
            flag2 = 1;
            flag3 = 1;
//            flag6 = 1;
            flag7 = 1;
        }
    }

}

int main(int argc, char** argv) {

    ros::init(argc, argv, "action_motor");
    ros::NodeHandle nh;

//    action_execution_msgs::Package msg_in;
//    action_execution_msgs::Command_result msg_out;
//    method = atof(argv[1]);//1 or 2
//    goal_velocity = atof(argv[2]);
//    goal_rotate_deg = atof(argv[3]);

    //ros::Publisher torque_ctrl_pub = nh.advertise<dynamixel_controller_msg::TorqueMsg>("torque", 100);
    ros::Publisher state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);
    //ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
    ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    ros::Subscriber motor_state_sub = nh.subscribe("Motor_state",10,msgCallback);
    ros::Publisher Command_result_pub = nh.advertise<action_execution_msgs::Command_result>("CommandResult", 100);

    //dynamixel_controller_msg::TorqueMsg torque_msg;
    dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    //torque_msg.torque = true;
    state_enable_msg.enable = 1;
    ros::Duration(0.5).sleep();
    //torque_ctrl_pub.publish(torque_msg);
    //state_enable_pub.publish(state_enable_msg);

    int sampling_freq = 5;
    ros::Rate loop_rate(sampling_freq);

    total_action = sizeof(method)/sizeof(int);
//    std::cout << total_action-1 << std::endl;

    //int vel_var[] = {2,2,2};
    //bool stop = false;
//    int flag6 = 1;
//    int flag7 = 1;

//    int vel = 1;
//    int vel_raw = vel*84;
//    int vel_left = 0;
//    int vel_right = 0;

//    int i = 0;

//    int cnt = 0;

	double x = 0.5 * 100;
	double y = 0.5 * 100;
	double angle = 0;
	
	if (x != 0) {
		angle = atan(y/x) * 180 / pi;
	} else if (y != 0) {
		angle = 90;
	}
	double angle_z = 180 * 0 - angle;
	int dist = sqrt(x*x + y*y);
	method[0] = 3;//1:forward, 2:backward, 3:left_turn, 4:right_turn, 0:stop
	method[1] = 1;
	method[2] = 4;
    method[3] = 3;

	goal_velocities[0] = 1;
	goal_velocities[1] = 3;
	goal_velocities[2] = 1;
	goal_velocities[3] = 0;


	distance_rotate[0] = (int)angle;
	distance_rotate[1] = dist;
	distance_rotate[2] = (int)angle_z;
	distance_rotate[3] = 0;
    while (ros::ok()) {

        state_enable_pub.publish(state_enable_msg);

        std::vector<uint32_t> ids;
        std::vector<uint32_t> positions;
        std::vector<int32_t> velocities;

        ids.push_back(7);
        ids.push_back(8);

        dynamixel_controller_msg::MotorControlMsg msg;

//        cnt = cnt + 1;

//        if (cnt > 50 || flag7 == 1)
//        {
//            while(flag6){std::cout << i+1 << "th action!" << std::endl;flag6 = 0;}
            vel_raw = goal_velocities[i]*40;
            switch(method[i])
            {
                case 1:
                    //flag7 = 0;
                    vel_left = vel_raw;
                    vel_right = -vel_raw;
                    while(flag7){std::cout << i+1 << "th action! " << "forward" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
                    break;
                case 2:
                    //flag7 = 0;
                    vel_left = -vel_raw;
                    vel_right = vel_raw;
                    while(flag7){std::cout << i+1 << "th action! " << "backward" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
                    break;
                case 3:
                    //flag7 = 0;
                    vel_left = vel_raw;
                    vel_right = vel_raw;
                    while(flag7){std::cout << i+1 << "th action! " << "left_turn" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
                    break;
                case 4:
                    //flag7 = 0;
                    vel_left = -vel_raw;
                    vel_right = -vel_raw;
                    while(flag7){std::cout << i+1 << "th action! " << "right_turn" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
                    break;
                case 0:
                    //flag7 = 0;
                    vel_left = 0;
                    vel_right = 0;
                    while(flag7){std::cout << "stop" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;flag3 = 0;}
                    if(i == total_action-1)
                    {
                        stop = true;
                    }
                    //else
                    //{
                    //    cnt = 200;
                    //}
                    //ros::shutdown();
                    break;
            }
            //std::cout << i << std::endl;
            //std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;
//            i = i + 1;
//            cnt = 0;
//        }

        velocities.push_back(vel_left);
        velocities.push_back(vel_right);
        //std::cout << "current vel of motor7_2: " << vel_left << " and motor 8_2: " << vel_right << std::endl;

        msg.motor_ids = ids;
        msg.positions = positions;
        msg.velocities = velocities;

        motor_ctrl_pub.publish(msg);

        //ros::spinOnce();

        loop_rate.sleep();

        if (stop)
        {
            //ros::NodeHandle nh_;
            //ros::Publisher Command_result_pub_ = nh_.advertise<action_execution_msgs::Command_result>("CommandResult", 100);
            action_execution_msgs::Command_result msg2_;
            msg2_.id = 78;
            msg2_.package_name = "ros_robot_navigation";
            msg2_.success = true;
            msg2_.error_id = 100;
            //std::cout<< msg2_.id <<std::endl;
            //std::cout<< msg2_.package_name <<std::endl;
            //std::cout<< msg2_.success <<std::endl;
            //std::cout<< msg2_.error_id <<std::endl;
            std::cout<< msg2_ <<std::endl;
            Command_result_pub.publish(msg2_);
            ros::shutdown();
        }
        ros::spinOnce();

    }
    ros::shutdown();
    return 0;
}

