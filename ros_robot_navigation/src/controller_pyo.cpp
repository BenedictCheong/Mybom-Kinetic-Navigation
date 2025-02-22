#include "ros/ros.h"
#include <iostream>

#include <stdio.h>
#include <dynamixel_controller_msg/MotorStateMsg.h>
#include <dynamixel_controller_msg/ModeControlMsg.h>
#include "dynamixel_controller_msg/MotorControlMsg.h"
//#include <dynamixel_controller_msg/TorqueMsg.h>

#include <boost/thread/thread.hpp>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

static struct termios initial_settings, new_settings;

static int peek_character = -1;

void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int _kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int _getch()
{
    char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}

int _putch(int c) {
    putchar(c);
    fflush(stdout);
    return c;
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "controller_pyo");
    ros::NodeHandle nh;

    std::vector<uint32_t> ids;
    ids.push_back(7);
    ids.push_back(8);
    int position1 = 2048;
    int position2 = 2048;
    int positions[2] = {position1, position2};
    int velocities[2] = {0, 0};
    int sampling_freq=20;

    int c_vel7=0;
    int c_vel8=0;

    ros::Rate loop_rate(sampling_freq);

//    ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("joint_controll", 100);
    ros::Publisher motor_ctrl_pub = nh.advertise<dynamixel_controller_msg::MotorControlMsg>("wheel_control", 100);
    ros::Publisher mode_pub = nh.advertise<dynamixel_controller_msg::ModeControlMsg>("Mode", 100);
    //ros::Publisher Torque_pub = nh.advertise<dynamixel_controller_msg::TorqueMsg>("torque", 100);

    //dynamixel_controller_msg::TorqueMsg torque_msg;
    //torque_msg.torque = true;
    ros::Duration(0.5).sleep();
    //Torque_pub.publish(torque_msg);


    init_keyboard();
    while (ros::ok()) {
        dynamixel_controller_msg::MotorControlMsg msg;

        std::vector<int> positions;
        std::vector<int> velocities;
        //int a = 0;
        //std::cout<<a++<<std::endl;
        int vel_ctrl_7;
        int vel_ctrl_8;
        if (_kbhit()) {
            vel_ctrl_7 = _getch();
            vel_ctrl_8 = _getch();
            _putch(vel_ctrl_7);
            _putch(vel_ctrl_8);
            if (vel_ctrl_7 == 'q') {
                c_vel7+=20;
            }
            if (vel_ctrl_7 == 'w') {
                c_vel7-=20;
            }
            if (vel_ctrl_8 == 'e') {
                c_vel8+=20;
            }
            if (vel_ctrl_8 == 'r') {
                c_vel8-=20;
            }
        }
        //c_vel7++;
        velocities.push_back(c_vel7);
        velocities.push_back(c_vel8);
        std::cout << "current vel of motor7: " << c_vel7 << " and motor 8: " << c_vel8 << std::endl;
        msg.motor_ids = ids;
        //msg.positions=positions;
        msg.velocities = velocities;

        motor_ctrl_pub.publish(msg);

        //ros::spinOnce();
        loop_rate.sleep();

    }
    close_keyboard();
    ros::shutdown();
    return 0;
}
