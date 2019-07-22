#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <stdio.h>

#include <action_execution_msgs/Package.h>
#include <action_execution_msgs/Data.h>
#include <action_execution_msgs/Command_result.h>

int id = 72;

void msgCallback(const action_execution_msgs::Command_result::ConstPtr& msg)
{
    if (id == msg->id)
    {
        std::cout<< msg->id <<std::endl;
        std::cout<< msg->package_name <<std::endl;
        std::cout<< msg->success <<std::endl;
        std::cout<< msg->error_id <<std::endl;
        ros::shutdown();
    }
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "action_motor_dumy");
    ros::NodeHandle nh;

    ros::Publisher motor_dumy_pub = nh.advertise<action_execution_msgs::Package>("robot_move_controller_package_msg", 100);

    ros::Duration(0.5).sleep(); // sleep for half a second
    action_execution_msgs::Package msg;

    //int id = 78;
    std::string package_name = "ros_robot_controller";
    std::vector<action_execution_msgs::Data> data_list;
    action_execution_msgs::Data d1, d2;
    d1.data_name = "position";
    d1.data_type = "float";
    d2.data_name = "orientation";
    d2.data_type = "float";
    std::vector<std::string> str1, str2;
    str1.push_back("2");
    str1.push_back("2");
    str1.push_back("2");
    str2.push_back("2");
    str2.push_back("2");
    str2.push_back("2");
    str2.push_back("2");
    d1.data_value_list = str1;
    d2.data_value_list = str2;
    data_list.push_back(d1);
    data_list.push_back(d2);

    msg.id = id;
    msg.package_name = package_name;
    msg.data_list = data_list;

    std::cout<< msg <<std::endl;

    motor_dumy_pub.publish(msg);

    ros::Subscriber Command_result_sub = nh.subscribe("command_result",10,msgCallback);

    ros::spin();
    return 0;
 }
