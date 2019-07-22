
#include "../include/NaviInterfaceNode.h"


using namespace std;
using namespace navi_interface;

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <move_base_msgs/MoveBaseActionGoal.h>

NaviInterfaceNode::NaviInterfaceNode()
{
	 mPackageName="ros_robot_navigation";
	 mPubResult = mNodeHandle.advertise<action_execution_msgs::Command_result>("/command_result", 10);
	 mPubPose = mNodeHandle.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10);
	 mPubMove = mNodeHandle.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 10);
	 mPubLog =mNodeHandle.advertise<std_msgs::String>("/navi_log", 10);
	 mID = -1;
	 mPackageName = "None";
	sendPose(0.f,0.f,0.f);
	//sendPose(-0.6, 0.9, -45*3.14/180.f);
	//cout<<"Navi_Instance()"<<endl;
}

NaviInterfaceNode::~NaviInterfaceNode()
{
	
}


//Test Command: rostopic pub /test_navi geometry_msgs/Point "x: 0.0 y: 0.0 z: 0.0" 
void NaviInterfaceNode::sendTestMsg(const geometry_msgs::Point::ConstPtr& msg)
{
	//cout<<"Get [Test_Command] msg.."<<endl;
	double x = msg ->x;
	double y = msg ->y;
	double z = msg ->z;
	
	//sendPose()
	//sendMove()
	//sendPose(x,y,z);
	sendMove(x,y,z);		
	sendLog("sendMove");

}

void NaviInterfaceNode::getCommand(const action_execution_msgs::Package::ConstPtr& msg)
{
	sendLog("getCommand");
	//cout<<"Get [Command] msg from Action/Task Execution"<<endl;
	mID = msg->id;
	mPackageName = msg->package_name;
	//sendResult(true);

//YJYJ

	vector<action_execution_msgs::Data> data_list = msg->data_list;

	double x, y, z = 0;
	for(int i=0; i< data_list.size(); i++)
	{
		if(data_list[i].data_name == "target_position")
		{
			if(strcmp("Null", data_list[i].data_value_list[0].c_str()) != 0 )
			{
				x = atof(data_list[i].data_value_list[0].c_str());
				y = atof(data_list[i].data_value_list[1].c_str());
				z = atof(data_list[i].data_value_list[2].c_str());
				sendMove(x,y,z);
				sendLog("sendMove");
			}

			
			
		}
		else if (data_list[i].data_name == "init_position")
		{
			if(strcmp("Null", data_list[i].data_value_list[0].c_str()) != 0 )
			{
				//x = atof(data_list[i].data_value_list[0].c_str());
				//y = atof(data_list[i].data_value_list[1].c_str());
				//z = atof(data_list[i].data_value_list[2].c_str());
				sendPose(0.f,0.f,0.f);
				sendLog("sendPose");
				sendResult(true);
			}
			
		}

	
	}
	
	

	//sendPose(x,y,z);
	//sendMove(x,y,z);
}


void NaviInterfaceNode::getResult(const std_msgs::Bool::ConstPtr& msg)
{
	//cout<<"Get [Result] msg from Navigation"<<endl;
	sendResult(msg->data);
}


void NaviInterfaceNode::sendPose(double x,double y, double theta)
{
	//you need to make this part and then send a msg by using "mPubPose"
	//you can use "x, y, z" in getCommand()

	// ...

	//mPubPose()
	//geometry_msgs::Point::ConstPtr msg;
	//getCommand(&msg);
	//double x,y,theta, ori_z, ori_w;
	std::string frame_id;
	frame_id = "map";
	m_initialPose.header.frame_id = frame_id;
	//x,y,z pose information	
	m_initialPose.pose.pose.position.x = x;
	m_initialPose.pose.pose.position.y = y;
	m_initialPose.pose.pose.position.z = 0;
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);
	//Quaternian orientation	
	m_initialPose.pose.pose.orientation = odom_quat;

	for(int i=0;i<36;i++)
		m_initialPose.pose.covariance[i] = 0.f;

	//.x = 0;
	//m_initialPose.pose.pose.orientation.y = 0;
	//m_initialPose.pose.pose.orientation.z = ori_z; //yaw
	//m_initialPose.pose.pose.orientation.w = ori_w;
	
	//ros::Publisher initial_pose = mNodeHandle.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose",10,true);
	//cout<<"[publish] initialize pose"<<endl;
	//cout<<"p.x:"<<m_initialPose.pose.pose.position.x<<endl;
	//cout<<"p.y:"<<m_initialPose.pose.pose.position.y<<endl;
	//cout<<"o.z:"<<m_initialPose.pose.pose.orientation.z<<endl;
	//cout<<"o.w:"<<m_initialPose.pose.pose.orientation.w<<endl;
	mPubPose.publish(m_initialPose);
}

void NaviInterfaceNode::NavStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr& status)
{
	stringstream ss, ss1;
	
	//geometry_msgs::Twist velocity;
	
	//cout<<"get Msg NavStatus"<<endl;
	if(!status->status_list.empty())
	{
		//ss << start;
		string str = ss.str();
		
		//ss1 << status->status_list[0].status;
		string str1 = ss1.str();
		//sendLog("Status: "+str1);
		ss1 << status->status_list.size();
		string str10 = ss1.str();
		sendLog("Status Size: "+str10);
			
		if ( status->status_list.size() == 1)
		{
			if (start == 0 && status->status_list[0].status == 1)
			{
				start = 1;//int prev_status = status->status_list[0];
				////cout<<"navigation command started!!!"<<endl;
				sendLog("navigation command started!!!");
				sendLog("Status: "+str1);
			}
		}
		else if ( status->status_list.size() == 2)
		{
			if ( start ==0 && (status->status_list[0].status == 1 || status->status_list[1].status == 1))
			{
				start = 1;//int prev_status = status->status_list[0];
				//cout<<"navigation command started!!!with 2 status"<<endl;
				sendLog("navigation command started!!!");
				sendLog("Status: "+str1);
				
			}
		}
		else if ( status->status_list.size() > 2)
		{
			for( int idx = 0; idx < status->status_list.size(); idx++)
			{
				if ( start ==0 && status->status_list[idx].status == 1)
				{
					start = 1;//int prev_status = status->status_list[0];
					//cout<<"navigation command started!!!with more than 2 status"<<endl;
					sendLog("navigation command started!!!with more than 2 status");
					sendLog("Status: "+str1);
				
				}
			}
		}
		
		m_status = status->status_list[0];//status->header.seq-3];

		if ( status->status_list.size() == 1)
		{
			sendLog("sendResult_(true)_error in 0");
			ss1 << status->status_list[0].status;
			string str1 = ss1.str();
			sendLog("Status: "+str1);
			if (start ==1 && m_status.status == 3)
			{
				success.data = true;
				//cout<<"success"<<endl<<m_status.status<<endl;
				//cout<<"publishing success flag"<<endl;
				sendLog("sendResult_(true)");
				sendResult(success.data);
				start = 0;
			}
			else if (start == 1 && m_status.status != 3 && m_status.status != 0 && m_status.status != 1)
			{
				//cout<<"navigation failed"<<endl;
				success.data = false;
				sendResult(success.data);
				sendLog("sendResult_(false)");
				start = 0;
			}
		}
		else if (status->status_list.size() == 2)
		{
			sendLog("sendResult_(true)_error in 1");
			ss1 << status->status_list[0].status;
			string str1 = ss1.str();
			sendLog("Status1: "+str1);
			ss1 << status->status_list[1].status;
			string str2 = ss1.str();
			sendLog("Status2: "+str2);
			ss1 << start;
			string str3 = ss1.str();
			sendLog("Status2: "+str3);
			if (start == 1 && (status->status_list[0].status == 3 && status->status_list[1].status == 3))
			{
				success.data = true;
				//cout<<"success with 2 status"<<endl<<status->status_list[1].status<<endl;
				//cout<<"publishing success flag"<<endl;
				sendLog("sendResult_(true)");
				sendResult(success.data);
				start = 0;
			}
			/*else if (start == 1 && (status->status_list[0].status == 3 && status->status_list[1].status == 3))
			{
				success.data = true;
				//cout<<"success with 2 status"<<endl<<status->status_list[1].status<<endl;
				//cout<<"publishing success flag"<<endl;
				sendLog("sendResult_(true)");
				sendResult(success.data);
				start = 0;
			}*/
			else if (start == 1 && status->status_list[1].status != 3 && status->status_list[1].status != 0 && status->status_list[1].status != 1)
			{
				//cout<<"navigation failed with 2 status"<<endl;
				success.data = false;
				sendResult(success.data);
				sendLog("sendResult_(false)");
				start = 0;
			} 
		}
		else if (status->status_list.size() > 2)
		{
			sendLog("sendResult_(true)_error in 2");
			for (int idx = 0; idx < status->status_list.size(); idx++)
			{
				ss1 << status->status_list[idx].status;
				string str1 = ss1.str();
				sendLog("Status: "+str1);
			}
			if (start == 1 && status->status_list[status->status_list.size()].status == 3 )
			{
				success.data = true;
				//cout<<"success with more than 2 status"<<endl<<status->status_list[status->status_list.size()].status<<endl;
				//cout<<"publishing success flag"<<endl;
				sendLog("sendResult_(true)");
				sendResult(success.data);
				start = 0;
			}
			else if (start == 1 && status->status_list[status->status_list.size()].status != 3 && status->status_list[status->status_list.size()].status != 0 && status->status_list[status->status_list.size()].status != 1)
			{
				//cout<<"navigation failed with more than 2 status"<<endl;
				success.data = false;
				sendResult(success.data);
				sendLog("sendResult_(false)");
				start = 0;
			} 
		}
/*		else if (start == 1 && m_status.status == 1)
	//	{
	//		//cout<<"navigation in progress"<<endl;
			//success.data = false;
			//sendResult(success.data);
			//sendLog("sendResult_(false)");
	//		start = 1;
	//	}
		else if (start == 1 && m_status.status == 2)
		{
			//cout<<"navigation get a cancel signal"<<endl;
			//success.data = false;
			//sendResult(success.data);
			sendLog("sendResult_(false)");
			start = 0;
		}*/
	}
	else if(status->status_list.empty())
	{
		sendLog("status list is empty!!");
	}
	
	//ROS_INFO("%s",m_status.status_list.text);
}




/*void NaviInterfaceNode::VelStatusCallback(const geometry_msgs::Twist velocity)
{
	if ( velocity.linear.x != 0 || velocity.linear.y != 0 || velocity.linear.z != 0 || velocity.angular.x != 0 || velocity.angular.y != 0 || velocity.angular.z != 0)
	{
		m_bVelInput = true;
	}
	else
	{
		m_bVelInput = false;
	}
}
*/


/*void NaviInterfaceNode::sendMove(double x,double y, double theta)
{
	//you need to make this part and then send a msg by using "mPubMove"
	//you can use "x, y, z" in getCommand()

	// ...

	//mPubMove()
	//double x,y,theta, ori_z, ori_w;
	std::string frame_id;
	frame_id = "map";
	m_goal_pose.goal.target_pose.header.frame_id = frame_id;
	//x,y,z pose information	
	m_goal_pose.goal.target_pose.pose.position.x = x;
	m_goal_pose.goal.target_pose.pose.position.y = y;
	m_goal_pose.goal.target_pose.pose.position.z = 0;
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);
	//Quaternian orientation	
	m_goal_pose.goal.target_pose.pose.orientation = odom_quat;

	//.x = 0;
	//m_initialPose.pose.pose.orientation.y = 0;
	//m_initialPose.pose.pose.orientation.z = ori_z; //yaw
	//m_initialPose.pose.pose.orientation.w = ori_w;
	
	//ros::Publisher pub_goal = mNodeHandle.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal",10,true);
	mPubMove.publish(m_goal_pose);
	//cout<<"publish goal pose"<<endl;

	success.data = false;
	
	//mSubStatus = mNodeHandle.advertise<actionlib_msgs::GoalStatusArray>("/move_base/status", 10);

	ros::Subscriber move_status = mNodeHandle.subscribe<actionlib_msgs::GoalStatusArray>("move_base/status",50,&NaviInterfaceNode::NavStatusCallback,this);
	while (m_status.status == 0 || m_status.status == 1)
//	{
		move_status = mNodeHandle.subscribe<actionlib_msgs::GoalStatusArray>("move_base/status",50,&NaviInterfaceNode::NavStatusCallback,this);
		//cout<<m_status.status<<endl;
		//ros::Subscriber Success
//	}
	////cout<<m_status.status_list[0]<<endl;
	if (m_status.status == 3)
		success.data = true;
	else
		success.data = false;
	
	//cout<<"publishing success flag"<<endl;
	sendResult(success.data);
	//mPubResult.publish(success);
}*/
void NaviInterfaceNode::sendMove(double x,double y, double theta)
{
	//you need to make this part and then send a msg by using "mPubMove"
	//you can use "x, y, z" in getCommand()

	// ...

	//mPubMove()
	//double x,y,theta, ori_z, ori_w;
	std::string frame_id;
	frame_id = "map";
	m_goal_pose.goal.target_pose.header.frame_id = frame_id;
	//x,y,z pose information	
	m_goal_pose.goal.target_pose.pose.position.x = x;
	m_goal_pose.goal.target_pose.pose.position.y = y;
	m_goal_pose.goal.target_pose.pose.position.z = 0;
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);
	//Quaternian orientation	
	m_goal_pose.goal.target_pose.pose.orientation = odom_quat;

	int prev_status = m_status.status;
	//cout<<"current status out:"<<prev_status<<endl;
	//ros::Publisher pub_goal = mNodeHandle.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal",10,true);
	mPubMove.publish(m_goal_pose);
	//cout<<"[publish] goal pose"<<endl;
	start = 0;
	success.data = false;
	
	//mSubStatus = mNodeHandle.advertise<actionlib_msgs::GoalStatusArray>("/move_base/status", 10); -> callback function 

//	ros::Subscriber move_status = mNodeHandle.subscribe<actionlib_msgs::GoalStatusArray>("move_base/status",50,&NaviInterfaceNode::NavStatusCallback,this);

/*	while ( prev_status == m_status.status )
	{
		//sleep(0.1);
		//cout<<"not working!!!!!"<<endl;
	}

	while (m_status.status == 0 || m_status.status == 1 )
	{
		//move_status = mNodeHandle.subscribe<actionlib_msgs::GoalStatusArray>("move_base/status",50,&NaviInterfaceNode::NavStatusCallback,this);
		//cout<<m_status.status<<endl;
		//sleep(0.1);
		//ros::Subscriber Success
	}
	//cout<<m_status.status<<endl;


	if (m_status.status == 3)
	{
		success.data = true;
		//cout<<"success"<<endl<<m_status.status<<endl;
	}
	else
		success.data = false;
	
	//cout<<"publishing success flag"<<endl;
	sendResult(success.data);
*/	//mPubResult.publish(success);
}

void NaviInterfaceNode::sendResult(bool result)
{
	action_execution_msgs::Command_result msg;
	msg.id = mID;
	msg.error_id = 100;
	msg.package_name = mPackageName;
	msg.success = result;
	mPubResult.publish(msg);
}
void NaviInterfaceNode::sendLog(string msg)
{
	std_msgs::String send_msg;
	send_msg.data =msg;
	mPubLog.publish(send_msg);
}


int main(int argc, char **argv) 
{
	    ros::init(argc, argv, "NavigationInterfaceNode");
		navi_interface::NaviInterfaceNode interfaceNode;
		ros::NodeHandle node;
	  	ros::Subscriber subCommand=node.subscribe<action_execution_msgs::Package>("/navigation_interface_msg", 10, &NaviInterfaceNode::getCommand, &interfaceNode);
		ros::Subscriber subResult=node.subscribe<std_msgs::Bool>("/done_sign_navi", 10, &NaviInterfaceNode::getResult, &interfaceNode);
		ros::Subscriber subStatus=node.subscribe<actionlib_msgs::GoalStatusArray>("move_base/status",100,&NaviInterfaceNode::NavStatusCallback,&interfaceNode);
		ros::Subscriber subTest=node.subscribe<geometry_msgs::Point>("/test_navi", 10, &NaviInterfaceNode::sendTestMsg, &interfaceNode);
		//ros::Subscriber subVelocity=node.subscribe<geometry_msgs::Twist>("/cmd_vel",100,&NaviInterfaceNode::VelStatusCallback,&interfaceNode);
		//ros::Subscriber subPose=node.subscribe<geometry_msgs::PoseStamped>("/base_position",100,&NaviInterfaceNode::PoseStatusCallback,&interfaceNode);
		ros::spin();
}
