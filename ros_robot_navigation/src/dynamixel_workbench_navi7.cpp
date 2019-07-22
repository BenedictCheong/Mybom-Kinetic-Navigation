/*******************************************************************************
* Copyright (c) 2016, ROBOTIS CO., LTD.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of ROBOTIS nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/* Author: Taehoon Lim (Darby) */
#include <ros/ros.h>
#include <dynamixel_workbench_msgs/SetDirection.h>
#include <dynamixel_workbench_msgs/SetDirection_navi.h>

#include <unistd.h>
#include <stdlib.h>
#include <std_msgs/String.h>
#include <stdio.h>
//#include <ros/ros.h>
//#include <dynamixel_workbench_toolbox/dynamixel_tool.h>
#include <dynamixel_workbench_msgs/MotorStateList.h>
#include <dynamixel_workbench_msgs/MotorStateList_Wheel.h>
//#include <dynamixel_workbench_msgs/MotorStateList_Neck.h>
//#include <dynamixel_workbench_msgs/SetPosition.h>
//#include <dynamixel_workbench_msgs/SetDirection.h>

//#include <dynamixel_sdk/dynamixel_sdk.h>

//#include <dynamixel_workbench_controllers/dynamixel_workbench_neck_wheel_control.h>
//using namespace dynamixel_workbench_neck_wheel_control;


float goal_velocity;//rad/sec
float goal_rotate_deg;//deg
//float goal_rotate_raw;//raw
float goal_velocity_left;
float goal_velocity_right;
//int start_position;
//int pre_odo;
int start_position_left;
int start_position_right;
int var_odo_left;
int var_odo_right;

//int oldposition_left;
int preposition_left;
//int oldposition_right;
int preposition_right;
int flag1=1;
int flag2=1;
int flag3=1;
int flag4=1;
int flag5=1;
int cc=0;
int dist=0;
int method;

void msgCallback(const dynamixel_workbench_msgs::MotorStateList::ConstPtr& dynamixel_response_list)
{
  preposition_left = dynamixel_response_list->motor_states[2].present_position;//left_wheel
  preposition_right = dynamixel_response_list->motor_states[3].present_position;//right_wheel
  while(flag1){start_position_left = preposition_left; flag1 = 0;}//when motor init, oldposition is "0" so, oldposition = preposition
  while(flag2){start_position_right = preposition_right; flag2 = 0;}
  while(flag3){ROS_INFO("start_position_left %d",start_position_left);ROS_INFO("start_position_right %d",start_position_right); flag3 = 0;};
  var_odo_left = abs(preposition_left-start_position_left);
  var_odo_right = abs(preposition_right-start_position_right);
  if (method == 2)
  {
      //dist = (int(abs(goal_rotate_deg*0.14486*144.8664))-int(goal_velocity*10.47125));
      dist = (int(abs(goal_rotate_deg*0.14*140))-int(goal_velocity*10.47125));
  }
  if (method == 1)
  {
      dist = (int(abs(goal_rotate_deg*144.8664))-int(goal_velocity*10.47125));
  }
  if ((var_odo_left*0.5+var_odo_right*0.5)>=dist)//cm -> raw + correction
//    if (abs(pre_odo-start_position)>=int(goal_rotate_deg*144.8664))//cm -> raw
  {
     //stop
      ros::NodeHandle nh_;
      dynamixel_workbench_msgs::SetDirection srv4;
      srv4.request.left_wheel_velocity = 0.0;
      srv4.request.right_wheel_velocity = 0.0;
      ros::ServiceClient dynamixel_workbench_navi7_client = nh_.serviceClient<dynamixel_workbench_msgs::SetDirection>("/dynamixel_workbench_tutorials/wheel");
      //ros::ServiceClient dynamixel_workbench_navi7_client = nh.serviceClient<dynamixel_workbench_msgs::SetDirection>("/dynamixel_workbench_tutorials/wheel");
      if (dynamixel_workbench_navi7_client.call(srv4))
    {
        while(flag4)
        {
          ROS_INFO("left_wheel_velocity %.2f",srv4.request.left_wheel_velocity);
          ROS_INFO("right_wheel_velocity %.2f",srv4.request.right_wheel_velocity);
          ROS_INFO("stop");
          //int end_position = pre_odo;
          int end_position_left = preposition_left;
          int end_position_rigft = preposition_right;
          ROS_INFO("stop_position_left %d",end_position_left);
          ROS_INFO("stop_position_right %d",end_position_rigft);
          flag4 = 0;
          //std::system("rosnode kill /dynamixel_workbench_navi7");
        }
    }
  }
  if(flag5==1 && dynamixel_response_list->motor_states[2].moving ==0 && dynamixel_response_list->motor_states[3].moving == 0)
  {
  //  std::cout << "moving_left " << dynamixel_response_list->motor_states[2].moving << std::endl;
  //  std::cout << "moving_right " << dynamixel_response_list->motor_states[3].moving << std::endl;
    flag1 = 1;
    flag2 = 1;
    flag3 = 1;
    flag4 = 1;
    flag5 = 1;
    cc = 0;
   // std::system("rosnode kill /dynamixel_workbench_navi7");
  //  std::cout << cc <<std::endl;
  }
  else
  {
      cc = cc + 1;
  }

}

bool naviCallback(dynamixel_workbench_msgs::SetDirection_navi::Request &req, dynamixel_workbench_msgs::SetDirection_navi::Response &res)
{
//    res.wheel_velocity = req.wheel_velocity;
//    res.rotate_deg = req.rotate_deg;
//    res.moving = 1;
    method = req.method;
    goal_velocity = req.wheel_velocity;
    goal_rotate_deg = req.rotate_deg;
    goal_velocity_left = goal_velocity;
    goal_velocity_right = goal_velocity;
    if (method == 2)
    {
        if (goal_rotate_deg>0)//left
        {
            goal_velocity_left = goal_velocity*(-1);
        }
        else
        {
            goal_velocity_right = goal_velocity*(-1);
        }
    }
    /*
    if (goal_rotate_deg>0)//left
    {
        goal_velocity_left = goal_velocity*(-1);
        goal_velocity_right = goal_velocity;
    }
    else
    {
        goal_velocity_left = goal_velocity;
        goal_velocity_right = goal_velocity*(-1);
    }
    */
    flag1 = 1;
    flag2 = 1;
    flag3 = 1;
    flag4 = 1;
    flag5 = 1;
    cc = 0;

    ros::NodeHandle nh4;
    dynamixel_workbench_msgs::SetDirection srv4;
    srv4.request.left_wheel_velocity = goal_velocity_left;
    srv4.request.right_wheel_velocity = goal_velocity_right;
    ros::ServiceClient dynamixel_workbench_navi7_client = nh4.serviceClient<dynamixel_workbench_msgs::SetDirection>("/dynamixel_workbench_tutorials/wheel");
    if (dynamixel_workbench_navi7_client.call(srv4))
  {
       res.moving = 1;
        std::cout << "moving" << std::endl;
       // ros::Subscriber dynamixel_workbench_navi7_sub = nh4.subscribe("/dynamixel_workbench_neck_wheel_control/motor_state",10,msgCallback);
    }

  //  dynamixel_workbench_msgs::MotorState_Wheel msg;
    //ros::Subscriber dynamixel_workbench_navi7_sub = nh.subscribe("/dynamixel_workbench_neck_wheel_control/motor_state_wheel",10,msgCallback);
    ros::Subscriber dynamixel_workbench_navi7_sub = nh4.subscribe("/dynamixel_workbench_neck_wheel_control/motor_state",10,msgCallback);
    /*if (flag5 == 0)
    {
      //std::cout << cc <<std::endl;
      res.moving = 0;
      std::cout << "stopping" << std::endl;
    }*/

    return true;
}

int main(int argc, char **argv)
{
  // Init ROS node
  ros::init(argc, argv, "dynamixel_workbench_navi7");
  dynamixel_workbench_msgs::SetDirection_navi srv;
  method = atof(argv[1]);//1 or 2
  goal_velocity = atof(argv[2]);
  goal_rotate_deg = atof(argv[3]);
  goal_velocity_left = goal_velocity;
  goal_velocity_right = goal_velocity;
  if (method == 2)
  {
      if (goal_rotate_deg>0)//left
      {
          goal_velocity_left = goal_velocity*(-1);
      }
      else
      {
          goal_velocity_right = goal_velocity*(-1);
      }
  }
  ROS_INFO("goal_velocity %.2f",goal_velocity);
  if (method==2)
  {
      ROS_INFO("goal_rotate_deg %.2f (+)left (-)right",goal_rotate_deg);
  }
  if (method==1)
  {
      ROS_INFO("goal_distance_cm %.2f",goal_rotate_deg);
  }
  ros::NodeHandle nh;

  ros::ServiceServer navi7_control_sever = nh.advertiseService("/dynamixel_workbench_tutorials/navi7", naviCallback);
  dynamixel_workbench_msgs::SetDirection srv4;
  srv4.request.left_wheel_velocity = goal_velocity_left;
  srv4.request.right_wheel_velocity = goal_velocity_right;
  ros::ServiceClient dynamixel_workbench_navi7_client = nh.serviceClient<dynamixel_workbench_msgs::SetDirection>("/dynamixel_workbench_tutorials/wheel");
  if (dynamixel_workbench_navi7_client.call(srv4))
{
  ROS_INFO("left_wheel_velocity %.2f",srv4.request.left_wheel_velocity);
  ROS_INFO("right_wheel_velocity %.2f",srv4.request.right_wheel_velocity);
}

//  dynamixel_workbench_msgs::MotorState_Wheel msg;
  ros::Subscriber dynamixel_workbench_navi7_sub = nh.subscribe("/dynamixel_workbench_neck_wheel_control/motor_state",10,msgCallback);

  ros::spin();

  return 0;
}

