#include <ros/ros.h>
#include <dynamixel_workbench_msgs/SetDirection.h>
#include <dynamixel_workbench_msgs/SetDirection_navi.h>
#include <dynamixel_workbench_msgs/SetDirection_odo2.h>
#include <dynamixel_workbench_msgs/SetDirection_turn2.h>

#include <unistd.h>
#include <stdlib.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <dynamixel_workbench_msgs/MotorStateList.h>
#include <dynamixel_workbench_msgs/SetPosition.h>
#include <dynamixel_workbench_msgs/SetPosition_ear.h>
#include <dynamixel_workbench_msgs/SetPosition_arm.h>

int ii=5;
int profile_method[] = {2, 1, 2, 1, 2};

float profile_vel[] = {1, 2, 1, 2, 1};
float profile_odo_rot[] = {-180, 135, 90, 190, 135};

int moving=0;
int i=0;
int c;
int cc=1;//10?

int a3;//=2;
int ai3=0;
int flag3=1;
float pf_ear_left[] = {270, 90};
float pf_ear_right[] = {270, 90};
int a4;//=4;
int ai4=0;
int flag4=1;
float pf_arm_left[] = {135, 45, 135, 90};
float pf_arm_right[] = {45, 135, 45, 90};
int a5;//=4;
int ai5=0;
int flag5=1;
float pf_pan[] = {195, 175, 195, 180, 180, 180};
float pf_tilt[] = {170, 200, 170, 200, 170, 200};

int moving_ear=1;
int c_ear;
int moving_arm=1;
int c_arm;
int moving_pt=1;
int c_pt;

int moving_next=0;

void msgCallback(const dynamixel_workbench_msgs::MotorStateList::ConstPtr& dynamixel_response_list)
{

        if(i<ii && moving!=1 && dynamixel_response_list->motor_states[2].moving ==0 && dynamixel_response_list->motor_states[3].moving == 0)
        {
           // std::system("rosrun dynamixel_workbench_tutorials dynamixel_workbench_navi7 0 0");
            ros::NodeHandle nh_;

                dynamixel_workbench_msgs::SetDirection_navi srv2;
                srv2.request.method = profile_method[i];
                srv2.request.wheel_velocity = profile_vel[i];
                srv2.request.rotate_deg = profile_odo_rot[i];
                ros::ServiceClient dynamixel_workbench_action5_client = nh_.serviceClient<dynamixel_workbench_msgs::SetDirection_navi>("/dynamixel_workbench_tutorials/navi7");
                if (dynamixel_workbench_action5_client.call(srv2))
              {
                    ROS_INFO("action%d!",profile_method[i]);
                    std::cout << i+1 << "th " << srv2.request.wheel_velocity << "/" << srv2.request.rotate_deg << std::endl;
                    moving = 1;
                    i++;                    
                    //std::cout << "c" << c << std::endl;//11
                    c=0;
                }

        }
        else if (c>cc)
        {
            moving = 0;
        }
        else
        {
            c++;
        }
        if (i>=ii && moving!=1 && dynamixel_response_list->motor_states[2].moving ==0 && dynamixel_response_list->motor_states[3].moving == 0)
        {
            moving_next=1;
        }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamixel_workbench_action5");
  a3 = sizeof(pf_ear_left)/sizeof(float);
  a4 = sizeof(pf_arm_left)/sizeof(float);
  a5 = sizeof(pf_pan)/sizeof(float);

  ros::NodeHandle nh;

  ros::Subscriber dynamixel_workbench_action5_sub = nh.subscribe("/dynamixel_workbench_neck_wheel_control/motor_state",10,msgCallback);

  ros::spin();

  return 0;
}
