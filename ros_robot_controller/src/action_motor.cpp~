
/*
이장우 수정 - 180807
콜백함수에 있던 while 제거
다량의 플래그 사용으로 인한 함수간의 의존성 제거
motor value -> state_request 퍼블리쉬 -> 동작 -> 모든 시퀀스가 완료되면
-> 상위에 Remsg 메세지를 보냄 -> state_request 종료
100ms 간격으로 state_request 송신(단, motor_value의 값이 들어오면..)
*/


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
float pi = 3.14159265359;
float wheel = 90;//94mm(blue),90mm(red)
int dist = 0;

float ratio1=(10*4096) / (wheel*pi);//distance
float ratio2=(4096*166*pi/360) / (wheel*pi);//rotate

ros::Publisher state_request_pub;
ros::Publisher motor_ctrl_pub;
ros::Publisher motor_Reinterface_pub;

//flag 선언
bool state_req_on=0;
int action_count=0;
bool odo_set=true;
bool stop = false;

void msgCallback_motor_value(const ros_robot_controller::msgTutorial::ConstPtr& msg)
{
	//std::cout << "===Motor_value_callback_start===" << std::endl;

	//motor_value 메세지의 method, vel, dist를 배열에 담는다.
	total_action = msg->method.size();
	for (int j = 0; j<total_action; j++)
	{
		method.push_back(msg->method[j]);
		goal_velocities.push_back(msg->goal_velocities[j]);
		distance_rotate.push_back(msg->distance_rotate[j]);
	}
	//std::cout << "total_action: " << total_action << std::endl;
	//std::cout << msg << std::endl;
	//std::cout << "===Motor_value_callback_end===" << std::endl;
	state_req_on=1;
	//state_request를 시작함
}


void msgCallback_motor_state(const dynamixel_controller_msg::MotorStateMsg::ConstPtr& msg)
{
	//std::cout << "===Motor_state_callback_start===" << std::endl;
	std::vector<uint32_t> ids;
	std::vector<int32_t> velocities;
	ids.push_back(7);
	ids.push_back(8);

	//Motor_Value값이 들어오면 //start
	//std::cout << "total_action: " << total_action << std::endl;
	//motor_value값이 잘 들어왔는지 확인
	for (int j = 0; j<total_action; j++)
	{
		std::cout << method[j] << std::endl;
		std::cout << goal_velocities[j] << std::endl;
		std::cout << distance_rotate[j] << std::endl;
	}
	//====calc======================

	preposition_left = msg->present_position[6];
	preposition_right = msg->present_position[7]*(-1);
	if(odo_set)
	//해당 거리만큼 갔을 때 odo_set이 false로 바뀐다.
	{
		start_position_left = preposition_left;
		start_position_right = preposition_right;
		odo_set=false;
	}

	var_odo_left = abs(preposition_left - start_position_left);
	var_odo_right = abs(preposition_right - start_position_right);
	if (method[action_count]==3 || method[action_count]==4)//turn
	{
			dist = (int(abs(distance_rotate[action_count]*ratio2))-int(goal_velocities[action_count]*10.47125*38));
	}
	if (method[action_count]==1 || method[action_count]==2)//forward, backward
	{
			dist = int(abs(distance_rotate[action_count]*ratio1));
	}
	if ((var_odo_left*0.5+var_odo_right*0.5)>=dist)
	//해당 거리만큼 갔을 경우 -> 0으로 셋
	{
			dynamixel_controller_msg::MotorControlMsg msg_;
			std::vector<uint32_t> ids_;
			std::vector<int32_t> velocities_;
			ids_.push_back(7);
			ids_.push_back(8);
			velocities_.push_back(0);
			velocities_.push_back(0);
			msg_.motor_ids = ids_;
			msg_.velocities = velocities_;
			motor_ctrl_pub.publish(msg_);
			odo_set=true;
			action_count+=1;
	}
	std::cout << "7" << std::endl;
	//std::cout << "===" << var_odo_left <<"===" << std::endl;
	//std::cout << "===" << var_odo_right <<"===" << std::endl;
	//std::cout << "===" << dist <<"===" << std::endl;
	if(action_count==total_action){
		method[action_count]=0;
	}
	//각각의 메소드에 맞는 바퀴 동작을 실행
	vel_raw = goal_velocities[action_count]*84;
	switch(method[action_count])
	{
		case 1:
			vel_left = vel_raw;
			vel_right = -vel_raw;
			//std::cout << action_count+1 << "th action! " << "forward" <<std::endl;
			//std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;
			break;
		case 2:
			vel_left = -vel_raw;
			vel_right = vel_raw;
			//std::cout << action_count+1 << "th action! " << "backward" <<std::endl;
			//std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;
			break;
		case 3:
			vel_left = vel_raw;
			vel_right = vel_raw;
			//std::cout << action_count+1 << "th action! " << "right_turn" <<std::endl;
			//std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;
			break;
		case 4:
			vel_left = -vel_raw;
			vel_right = -vel_raw;
			//std::cout << action_count+1 << "th action! " << "left_turn" <<std::endl;
			//std::cout << "current_velocities: " << vel_raw/84 << " (rad/s)" << std::endl;
			break;
		default:
			vel_left = 0;
			vel_right = 0;
			std::cout << "stop" <<std::endl;
			stop = true;
			break;
	}
	std::cout << action_count  << std::endl;
	std::cout << stop << std::endl;
	//마지막 method가 들어가면 stop
	if(stop)
	{
		state_req_on=0;
		ros_robot_controller::RemsgTutorial Remsg;
		stop = false;
		//motor_interface로 remsg 퍼블리쉬
		Remsg.success = true;
		Remsg.error_id = 100;
		motor_Reinterface_pub.publish(Remsg);

		for (int j=0;j<total_action;j++)
		{
			method.pop_back();
			goal_velocities.pop_back();
			distance_rotate.pop_back();
		}
		action_count=0;
		dynamixel_controller_msg::MotorControlMsg msg_;
		std::vector<uint32_t> ids_;
		std::vector<int32_t> velocities_;
		ids_.push_back(7);
		ids_.push_back(8);
		velocities_.push_back(0);
		velocities_.push_back(0);
		msg_.motor_ids = ids_;
		msg_.velocities = velocities_;
		motor_ctrl_pub.publish(msg_);
	}
	//Motor_Value값이 들어오면 //end

	//stop 상황이 아닌, 일반적인 동작일때 값들을 퍼블리쉬
	else if(state_req_on)
	{
		velocities.push_back(vel_left);
		velocities.push_back(vel_right);
		dynamixel_controller_msg::MotorControlMsg wheelmsg;
		wheelmsg.motor_ids = ids;
		wheelmsg.velocities = velocities;
		motor_ctrl_pub.publish(wheelmsg);
	}
	//모터스테이트
	//std::cout << "===Motor_state_callback_end===" << std::endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "action_motor");
  ros::NodeHandle nh;

  ros::Subscriber motor_value_sub = nh.subscribe("Motor_value",1000,msgCallback_motor_value);
  ros::Subscriber motor_state_sub = nh.subscribe("Motor_state",1000,msgCallback_motor_state);

  state_request_pub=nh.advertise<dynamixel_controller_msg::StateEnableMsg>("state_request", 100);
  motor_ctrl_pub=nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
  motor_Reinterface_pub=nh.advertise<ros_robot_controller::RemsgTutorial>("RemsgTutorial_value", 100);

  dynamixel_controller_msg::StateEnableMsg state_request_msg;
  state_request_msg.enable = 0;

  int sampling_freq = 10;
  ros::Rate loop_rate(sampling_freq);
  //ros while의 주기를 100hz

  while(ros::ok())
  {
		if(state_req_on)
		//motor_value값이 들어오면 state_req가 시작
		{
			//std::cout << "===state_request_publish===" << std::endl;
	    state_request_pub.publish(state_request_msg);
		}
    ros::spinOnce();
    loop_rate.sleep();
  }
  ros::spin();
  return 0;
}
