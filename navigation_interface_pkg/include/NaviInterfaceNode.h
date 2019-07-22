#ifndef NAVI_INTERFACE_NODE_H_
#define NAVI_INTERFACE_NODE_H_


#include <ros/ros.h>
#include <ros/package.h>
#include <string>
#include <vector>
#include <iostream>

#include "action_execution_msgs/Command_result.h"
#include "action_execution_msgs/Package.h"
#include "action_execution_msgs/Data.h"

#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseActionResult.h> //howon
#include <geometry_msgs/Quaternion.h> //howon
#include <tf/transform_broadcaster.h> //howon
#include <actionlib_msgs/GoalStatusArray.h> //howon
#include <stdio.h>
#include <stdlib.h>

using namespace std;
namespace navi_interface{
  class NaviInterfaceNode {
    public:
    NaviInterfaceNode();
    ~NaviInterfaceNode();    
    void getCommand(const action_execution_msgs::Package::ConstPtr& msg);
    void sendTestMsg(const geometry_msgs::Point::ConstPtr& msg);

    //You need to customize input parameters!!
    void sendPose(double x,double y, double theta);
    void sendMove(double x,double y, double theta);

    //get msg from [navi package] and send msg to [action/task execution]
    //test command: rostopic pub /done_sign_navi std_msgs/Bool "data: true"
    void getResult(const std_msgs::Bool::ConstPtr& msg);
    void sendResult(bool result);
    void sendLog(string msg);

    public:
    string mPackageName;
    int mID;

    ros::NodeHandle mNodeHandle;
    ros::Publisher mPubPose;
    ros::Publisher mPubMove;
    ros::Publisher mPubResult;
    ros::Publisher mPubLog;

    geometry_msgs::PoseWithCovarianceStamped m_initialPose;
    move_base_msgs::MoveBaseActionGoal m_goal_pose;
    actionlib_msgs::GoalStatus m_status;
    void NavStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr& status);
    std_msgs::Bool success;
    int start;
 //   void VelStatusCallback(const geometry_msgs::Twist velocity);
   // bool m_bVelInput;
    //move_base_msgs::MoveBaseAction m_actionResult;
    };
}





#endif //_NAVI_INTERFACE_NODE_H_
