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

std::vector<int> method;//1:forward, 2:backward, 3:right_turn, 4:left_turn, 0:stop
std::vector<int> goal_velocities;//rad/s
std::vector<int> distance_rotate;//cm or deg

int i = 0;
int flagi = 0;
int flagj = 0;
int vel_raw;
int vel_left = 0;
int vel_right = 0;

int total_action = 1;
bool in = true;

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
float pi = 3.14159265359;
float ratio1;//distance
float ratio2;//rotate
float wheel = 90;//94mm(blue),90mm(red)

int flag7 = 1;
bool stop = false;
int flag0 = 0;

ros::Publisher state_enable_pub;
ros::Publisher motor_ctrl_pub;
ros::Publisher motor_Reinterface_pub;

void msgCallback_value(const ros_robot_controller::msgTutorial::ConstPtr& msg)
{
//    std::cout << "s1" << std::endl;
    if(flagi == 0){
        total_action = msg->method.size();
        //std::cout<< total_action <<std::endl;
        for (int j=0;j<total_action;j++)
        {
            method.push_back(msg->method[j]);
            goal_velocities.push_back(msg->goal_velocities[j]);
            distance_rotate.push_back(msg->distance_rotate[j]);
            //std::cout<< j <<std::endl;
        }
        std::cout<< "total_action: " << total_action <<std::endl;
        in = false;
        flag7 = 1;
        flag0 = 1;
        flagi = 1;
    }

}

void msgCallback(const dynamixel_controller_msg::MotorStateMsg::ConstPtr& msg)
{
    if(flagj){
        ratio1 = (10*4096) / (wheel*pi);
        ratio2 = (4096*166*pi/360) / (wheel*pi);
        preposition_left = msg->present_position[6];
        preposition_right = msg->present_position[7]*(-1);
        //preposition_left = msg->present_position[0];
        //preposition_right = msg->present_position[1]*(-1);

        //if(flag1){start_position_left = preposition_left;flag1 = 0;}
        while(flag1){start_position_left = preposition_left;flag1 = 0;}
        //if(flag2){start_position_right = preposition_right;flag2 = 0;}
        while(flag2){start_position_right = preposition_right;flag2 = 0;}
        var_odo_left = abs(preposition_left - start_position_left);
        var_odo_right = abs(preposition_right - start_position_right);
        if (method[i]==3 || method[i]==4)//turn
        {
            //dist = int(abs(distance_rotate[i]*ratio2));
            dist = (int(abs(distance_rotate[i]*ratio2))-int(goal_velocities[i]*10.47125*38));
            //dist = (int(abs(distance_rotate[i]*0.14*140))-int(goal_velocities[i]*10.47125));
            //dist = int(abs(distance_rotate[i]*0.14*140));
        }
        if (method[i]==1 || method[i]==2)//forward, backward
        {
            dist = int(abs(distance_rotate[i]*ratio1));
            //dist = (int(abs(distance_rotate[i]*ratio1))-int(goal_velocities[i]*10.47125));
            //dist = (int(abs(distance_rotate[i]*144.8664))-int(goal_velocities[i]*10.47125));
            //dist = int(abs(distance_rotate[i]*144.8664));
        }
        if ((var_odo_left*0.5+var_odo_right*0.5)>=dist)
        {
            dynamixel_controller_msg::MotorControlMsg msg_;

            std::vector<uint32_t> ids_;
            //std::vector<uint32_t> positions_;
            std::vector<int32_t> velocities_;

            ids_.push_back(7);
            ids_.push_back(8);
            velocities_.push_back(0);
            velocities_.push_back(0);
            msg_.motor_ids = ids_;
            //msg_.positions = positions_;
            msg_.velocities = velocities_;

            motor_ctrl_pub.publish(msg_);
            /*if (dist != 0)
            {
                motor_ctrl_pub.publish(msg_);
            }*/
            i = i + 1;
            flag1 = 1;
            flag2 = 1;
            flag3 = 1;
            flag7 = 1;
            flagi = 1;
            flagj = 0;
            //out = true;

        }
    }

}

int main(int argc, char** argv) {

    ros::init(argc, argv, "action_motor");
    ros::NodeHandle nh;

    ros::Subscriber motor_value_sub = nh.subscribe("Motor_value",10,msgCallback_value);
    //state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_enable", 100);
    state_enable_pub = nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);
    //motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("Motor_ctrl", 100);
    motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
    ros::Subscriber motor_state_sub = nh.subscribe("Motor_state",10,msgCallback);
    motor_Reinterface_pub = nh.advertise<ros_robot_controller::RemsgTutorial>("RemsgTutorial_value", 100);

    dynamixel_controller_msg::StateEnableMsg state_enable_msg;
    state_enable_msg.enable = 0;

    int sampling_freq = 10;
    ros::Rate loop_rate(sampling_freq);

//    std::cout << "w1" << std::endl;
    dynamixel_controller_msg::MotorControlMsg msg;
    ros_robot_controller::RemsgTutorial msg2_;


    while (ros::ok())
    {
	if(flag0){state_enable_pub.publish(state_enable_msg);}
//        std::cout << "w2" << std::endl;

        std::vector<uint32_t> ids;
        //std::vector<uint32_t> positions;
        std::vector<int32_t> velocities;

        ids.push_back(7);
        ids.push_back(8);

	if(i==total_action){
		method[i]=0;
	}

        if(flagi){
            vel_raw = goal_velocities[i]*84;
            flagi = 0;
	    //std::cout<< i <<std::endl;
           switch(method[i])
            {
                case 1:
                    //flag7 = 0;
                    vel_left = vel_raw;
                    vel_right = -vel_raw;
                    //if(flag7){std::cout << i+1 << "th action! " << "forward" <<std::endl;flag7 = 0;}
                    //if(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    while(flag7){std::cout << i+1 << "th action! " << "forward" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    flagj = 1;
                    break;
                case 2:
                    //flag7 = 0;
                    vel_left = -vel_raw;
                    vel_right = vel_raw;
                    //if(flag7){std::cout << i+1 << "th action! " << "backward" <<std::endl;flag7 = 0;}
                    //if(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}

                    while(flag7){std::cout << i+1 << "th action! " << "backward" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    flagj = 1;
                    break;
                case 3:
                    //flag7 = 0;
                    vel_left = vel_raw;
                    vel_right = vel_raw;
                    //if(flag7){std::cout << i+1 << "th action! " << "right_turn" <<std::endl;flag7 = 0;}
                    //if(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    while(flag7){std::cout << i+1 << "th action! " << "right_turn" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    flagj = 1;
                    break;
                case 4:
                    //flag7 = 0;
                    vel_left = -vel_raw;
                    vel_right = -vel_raw;
                    //if(flag7){std::cout << i+1 << "th action! " << "left_turn" <<std::endl;flag7 = 0;}
                    //if(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    while(flag7){std::cout << i+1 << "th action! " << "left_turn" <<std::endl;flag7 = 0;}
                    while(flag3){std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;flag3 = 0;}
                    flagj = 1;
                    break;
                default:
                    //flag7 = 0;
                    vel_left = 0;
                    vel_right = 0;
                    //if(flag7){std::cout << "stop" <<std::endl;flag7 = 0;}
                    while(flag7){std::cout << "stop" <<std::endl;flag7 = 0;}
                    stop = true;
                    //i = 0;
                    //msg2_.success = true;
                    //msg2_.error_id = 100;
                    if (stop)
                    {
                        //out = false;
                        in = true;
                        stop = false;
                        //i = 0;
                        //ros_robot_controller::RemsgTutorial msg2_;
                        msg2_.success = true;
                        msg2_.error_id = 100;
                        while(flag0){motor_Reinterface_pub.publish(msg2_);flag0 = 0;}
                        //flag7 = 1;
                        flagi = 0;

                        //123 123 123
                        for (int j=0;j<total_action;j++)
                        {
                            method.pop_back();
                            goal_velocities.pop_back();
                            distance_rotate.pop_back();

			    //std::cout << "pop_back" <<std::endl;
			    //std::cout << method.size() <<std::endl;
                        }
                        i = 0;
			//flagi=0;

                        //123 456 789
                        /*for (int j=0;j<total_action;j++)
                        {
                            method.pop_back();
                            goal_velocities.pop_back();
                            distance_rotate.pop_back();
                        }*/

                    }
                    //ros::shutdown();
                    break;
            }
           velocities.push_back(vel_left);
           velocities.push_back(vel_right);

           msg.motor_ids = ids;
           //msg.positions = positions;
           msg.velocities = velocities;

           motor_ctrl_pub.publish(msg);
	   std::cout<<"msg(motor_ctrl_pub) send!"<<std::endl;

        }

        /*velocities.push_back(vel_left);
        velocities.push_back(vel_right);

        msg.motor_ids = ids;
        msg.positions = positions;
        msg.velocities = velocities;

        //motor_ctrl_pub.publish(msg);
        /*if (dist != 0)
        {
            motor_ctrl_pub.publish(msg);
        }*/

        ros::spinOnce();
        loop_rate.sleep();


    }

    ros::spin();

    return 0;
}
