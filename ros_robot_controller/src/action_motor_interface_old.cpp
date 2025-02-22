#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <stdio.h>

#include <action_execution_msgs/Package.h>
#include <action_execution_msgs/Command_result.h>
#include <ros_robot_controller/msgTutorial.h>
#include <ros_robot_controller/RemsgTutorial.h>

std::vector<int> val1, val2, val3;

int flag1;
int flag2;
bool error;
int id;
std::string package_name;
bool success;
int error_id;

//int method[] = {3,1,4};//1:forward, 2:backward, 3:right_turn, 4:left_turn, 0:stop
//int goal_velocities[] = {1, 2, 1};//rad/s
//int distance_rotate[] = {180, 180, 180};//cm or deg
//int method[] = {4,1,3};//1:forward, 2:backward, 3:right_turn, 4:left_turn, 0:stop
//int goal_velocities[] = {1, 2, 1};//rad/s
//int distance_rotate[] = {90, 60, 90};//cm or deg
//int total_action = 3;
int total_action;


ros::Publisher motor_interface_pub;
ros::Publisher Command_result_pub;

void msgCallback(const action_execution_msgs::Package::ConstPtr& msg)
{
    //std::cout<<"action_execution_msgs::get MSG!!"<<std::endl;
    id = msg->id;
    package_name = msg->package_name;

    //if (msg->data_list[0].data_value_list[0] == "1" && msg->data_list[0].data_value_list[1] == "1" && msg->data_list[0].data_value_list[2] == "1")
    //{
    //    flag1 = 1;
    //}
    //if (msg->data_list[1].data_value_list[0] == "1" && msg->data_list[1].data_value_list[1] == "1" && msg->data_list[1].data_value_list[2] == "1" && msg->data_list[1].data_value_list[3] == "1" )
    //{
    //    flag2 = 1;
    //}

    /*
    if (msg->data_list[0].data_value_list[0] == "1")
    {
        std::cout<< "1" <<std::endl;
        //val1.push_back(3);
        //val1.push_back(1);
        //val1.push_back(4);
        //val2.push_back(1);
        //val2.push_back(2);
        //val2.push_back(1);
        //val3.push_back(90);
        //val3.push_back(80);
        //val3.push_back(90);
        val1.push_back(4);
        val1.push_back(1);
        val1.push_back(3);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(1);
        val3.push_back(90);
        val3.push_back(90);
        val3.push_back(90);
    }
    else
    {
        std::cout<< "2" <<std::endl;
        //val1.push_back(4);
        //val1.push_back(1);
        //val1.push_back(3);
        //val2.push_back(1);
        //val2.push_back(3);
        //val2.push_back(1);
        //val3.push_back(180);
        //val3.push_back(180);
        //val3.push_back(230);
        val1.push_back(4);
        val1.push_back(1);
        val1.push_back(4);
        val1.push_back(1);
        val1.push_back(4);
        val2.push_back(1);
        val2.push_back(4);
        val2.push_back(1);
        val2.push_back(4);
        val2.push_back(1);
        val3.push_back(90);
        val3.push_back(120);
        val3.push_back(90);
        val3.push_back(150);
        val3.push_back(180);
    }
    */

    if (msg->data_list[0].data_value_list[0] == "1")
    {
	//1: foward, 2:backward, 3: right, 4: left
        std::cout<< "1" <<std::endl;
        total_action = 2;
        val1.push_back(4);
	val1.push_back(1);
	//method
        val2.push_back(1);
	val2.push_back(2);
	//vel
        val3.push_back(175);
	val3.push_back(100);
	//deg
    }
    else if (msg->data_list[0].data_value_list[0] == "2")
    {
        std::cout<< "2" <<std::endl;
	/*
	total_action = 3;
        val1.push_back(3);
        val1.push_back(1);
        val1.push_back(3);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(1);
        val3.push_back(180);
        val3.push_back(80);
        val3.push_back(90);
	*/
	total_action = 2;
	val1.push_back(3);
        val1.push_back(1);
        val2.push_back(1);
        val2.push_back(2);
        val3.push_back(130);
        val3.push_back(60);
    }
    else if (msg->data_list[0].data_value_list[0] == "3")
    {
        std::cout<< "3" <<std::endl;
        total_action = 3;
        val1.push_back(4);
        val1.push_back(1);
        val1.push_back(4);
        val2.push_back(1);
        val2.push_back(3);
        val2.push_back(1);
        val3.push_back(180);
        val3.push_back(270);//400
        val3.push_back(90);
    }
    else if (msg->data_list[0].data_value_list[0] == "4")
    {
        std::cout<< "4" <<std::endl;
        total_action = 2;
        val1.push_back(4);
        val1.push_back(1);
        val2.push_back(1);
        val2.push_back(3);
        val3.push_back(90);
        val3.push_back(270);//400
    }

    else if (msg->data_list[0].data_value_list[0] == "5")
    {//음악재생
        std::cout<< "5" <<std::endl;
        total_action = 3;
        val1.push_back(3);
        val1.push_back(1);
        val1.push_back(3);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(1);
        val3.push_back(165);
        val3.push_back(250);
        val3.push_back(30);
    }
    else if (msg->data_list[0].data_value_list[0] == "6")
    {//음악재생
        std::cout<< "6" <<std::endl;
        total_action = 2;
        val1.push_back(3);
        val1.push_back(1);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(2);
        val3.push_back(30);
        val3.push_back(165);
        val3.push_back(250);
    }
    /*
    else if (msg->data_list[0].data_value_list[0] == "5")
    {
        std::cout<< "5" <<std::endl;
        total_action = 3;
        val1.push_back(3);
        val1.push_back(1);
        val1.push_back(4);
        val2.push_back(1);
        val2.push_back(3);
        val2.push_back(1);
        val3.push_back(90);
        val3.push_back(150);
        val3.push_back(90);
    }*/
    else if (msg->data_list[0].data_value_list[0] == "11")
    {
        std::cout<< "11" <<std::endl;
        total_action = 3;
        val1.push_back(4);
        val1.push_back(1);
        val1.push_back(4);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(1);
        val3.push_back(95);
        val3.push_back(150);
        val3.push_back(30);
    }
    else if (msg->data_list[0].data_value_list[0] == "12")
    {
        std::cout<< "12" <<std::endl;
        total_action = 1;
        val1.push_back(3);
        val2.push_back(1);
        val3.push_back(60);
    }
    else if (msg->data_list[0].data_value_list[0] == "13")
    {
        std::cout<< "13" <<std::endl;
        total_action = 3;
        val1.push_back(3);
        val1.push_back(1);
        val1.push_back(4);
        val2.push_back(1);
        val2.push_back(2);
        val2.push_back(1);
        val3.push_back(120);
        val3.push_back(200);
        val3.push_back(170);
    }
    else if (msg->data_list[0].data_value_list[0] == "14")
    {
        std::cout<< "14" <<std::endl;
        total_action = 1;
        val1.push_back(3);
        val2.push_back(2);
        val3.push_back(100);
    }


    //if (flag1 == 1 && flag2 == 1)
    //{
        error = false;
    //}
    //else
    //{
    //    error  = true;
    //}
/*
    if (id == 79)
    {
        total_action = 1;
        val1.push_back(2);
        //val1.push_back(0);
        val2.push_back(2);
        //val2.push_back(0);
        val3.push_back(90);
        //val3.push_back(0);
        total_action = 1;
        //std::cout<< 1 <<std::endl;
    }
    else
    {*/
        //total_action = sizeof(method)/sizeof(int);
        //std::cout<< total_action <<std::endl;
            //for (int j=0;j<total_action;j++)
            //{
            //    val1.push_back(method[j]);
            //    val2.push_back(goal_velocities[j]);
            //    val3.push_back(distance_rotate[j]);
            //}
        /*
            val1.push_back(3);
            val1.push_back(1);
            val1.push_back(4);
            val2.push_back(1);
            val2.push_back(3);
            val2.push_back(1);
            val3.push_back(180);
            val3.push_back(180);
            val3.push_back(180);*/
//    }
    ros_robot_controller::msgTutorial msg_;

    msg_.method = val1;
    msg_.goal_velocities = val2;
    msg_.distance_rotate = val3;

    std::cout<< msg_ <<std::endl;
    motor_interface_pub.publish(msg_);

/*
    for (int j=0;j<total_action;j++)
    {
        val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
*/
    if (msg->data_list[0].data_value_list[0] == "1")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "2")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	/*
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	*/
    }
    else if (msg->data_list[0].data_value_list[0] == "3")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "4")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }

    else if (msg->data_list[0].data_value_list[0] == "5")
    {
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "6")
    {
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
      val1.pop_back();
      val2.pop_back();
      val3.pop_back();
    }

    else if (msg->data_list[0].data_value_list[0] == "11")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "12")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "13")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }
    else if (msg->data_list[0].data_value_list[0] == "14")
    {
	val1.pop_back();
        val2.pop_back();
        val3.pop_back();
    }

    /*
    val1.pop_back();
    val2.pop_back();
    val3.pop_back();
    val1.pop_back();
    val2.pop_back();
    val3.pop_back();
    val1.pop_back();
    val2.pop_back();
    val3.pop_back();*/

}

void RemsgCallback(const ros_robot_controller::RemsgTutorial::ConstPtr& msg)
{
    //std::cout<<"RemsgCallback::get MSG!!"<<std::endl;
    action_execution_msgs::Command_result msg_2;

    msg_2.id = id;
    msg_2.package_name = package_name;
    if (error)
    {
        msg_2.success = false;
        msg_2.error_id = 103;
    }
    else
    {
        msg_2.success = msg->success;
        msg_2.error_id = msg->error_id;
    }

    std::cout<< msg_2 <<std::endl;
    Command_result_pub.publish(msg_2);
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "action_motor_interface");
    ros::NodeHandle nh;
    motor_interface_pub = nh.advertise<ros_robot_controller::msgTutorial>("Motor_value", 100);
    //Command_result_pub = nh.advertise<action_execution_msgs::Command_result>("CommandResult_value", 100);
    Command_result_pub = nh.advertise<action_execution_msgs::Command_result>("command_result", 100);

    //ros::Subscriber motor_interface_sub = nh.subscribe("Package_value",10,msgCallback);
    ros::Subscriber motor_interface_sub = nh.subscribe("robot_move_controller_package_msg",10,msgCallback);
    //while(in){ros::spinOnce();}

    ros::Subscriber motor_Reinterface_sub = nh.subscribe("RemsgTutorial_value",10,RemsgCallback);
    //while(out){ros::spinOnce();}
    ros::spin();
    return 0;
}
