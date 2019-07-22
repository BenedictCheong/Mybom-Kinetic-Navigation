#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include <action_execution_msgs/Package.h>
#include <action_execution_msgs/Command_result.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib_msgs/GoalStatus.h>
#include <std_msgs/Header.h>


std::vector<int> val1, val2, val3;


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


ros::Publisher navigation_goal_pub;
ros::Publisher navigation_result_pub;

void navigationGoalCallback(const action_execution_msgs::Package::ConstPtr& msg)
{
    std::cout<<"receive navigation goal from behavior management"<< msg <<std::endl;
    id = msg->id;
    package_name = msg->package_name;

    //if (msg->data_list[0].data_value_list[0] == "1")

    move_base_msgs::MoveBaseActionGoal actionGoal;
    move_base_msgs::MoveBaseGoal goalInput;

    std_msgs::Header header;
    geometry_msgs::Pose pose;
    geometry_msgs::Point position;
    geometry_msgs::Quaternion orientation;
    geometry_msgs::PoseStamped poseStamped;
    actionlib_msgs::GoalID goalID;


    ros::Time time = ros::Time::now();
    header.stamp = time;
    header.seq = id;
    header.frame_id = "";
    actionGoal.header = header;

    position.x = std::atof(msg->data_list[0].data_value_list[0].c_str());
    position.y = std::atof(msg->data_list[0].data_value_list[1].c_str());
    position.z = std::atof(msg->data_list[0].data_value_list[2].c_str());

    pose.position = position;

    orientation.x = std::atof(msg->data_list[1].data_value_list[0].c_str());
    orientation.y = std::atof(msg->data_list[1].data_value_list[1].c_str());
    orientation.z = std::atof(msg->data_list[1].data_value_list[2].c_str());
    orientation.w = std::atof(msg->data_list[1].data_value_list[3].c_str());

    pose.orientation = orientation;
    header.frame_id = "map";
    poseStamped.header = header;
    poseStamped.pose = pose;

    goalID.stamp = time;
    goalID.id = id;

   // actionGoal.goal_id = goalID;

    //actionGoal.goal_id = "";

    goalInput.target_pose = poseStamped;

    actionGoal.goal = goalInput;

    std::cout<< "send navigation goal to navigation node"<< navigation_goal_pub <<std::endl;
    navigation_goal_pub.publish(actionGoal);

}

void navigationResultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg)
{
    std::cout<<"receive navigation result from navigation node"<< msg <<std::endl;
    action_execution_msgs::Command_result navigation_result;
    actionlib_msgs::GoalStatus goal_status;
    actionlib_msgs::GoalID goalID;

/*
 * uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server
*/

    goal_status = msg->status;
   // goalID = msg->status.goal_id;
    navigation_result.id = id;
    navigation_result.package_name = package_name;
    if(goal_status.status == 3){
        navigation_result.success = true;
    }else{
        navigation_result.success = false;
    }
    navigation_result.error_id = goal_status.status;

    std::cout<< "send navigation result to behavior management"<< navigation_result <<std::endl;
    navigation_result_pub.publish(navigation_result);
}



int main(int argc, char** argv) {

    ros::init(argc, argv, "navigation_interface");
    ros::NodeHandle nh;
    std::cout<<"start navigation interface"<<std::endl;

    navigation_goal_pub = nh.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal", 100);
    navigation_result_pub = nh.advertise<action_execution_msgs::Command_result>("command_result", 100);

    ros::Subscriber navigation_interface_sub = nh.subscribe("navigation_package_msg",10, navigationGoalCallback);
    //while(in){ros::spinOnce();}

    ros::Subscriber navigation_result_sub = nh.subscribe("move_base/result",10,navigationResultCallback);
    //while(out){ros::spinOnce();}
    ros::spin();
    return 0;
}
