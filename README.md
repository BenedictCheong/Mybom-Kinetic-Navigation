NavigationSetupforMybom
===========================================================

## 1. Description

NavigationSetupforMybom: Mybom의 Realsense R200 camera 를 이용한 자율 주행 Module 의 설치 및 setup

## 2. Getting Started

### 2.1 Requirements
-	[ROS](http://wiki.ros.org/) - Robot Operating System.


### 2.2 Install Guide
#### 1. Perception PC

```
cd catkin_ws/src
sudo git clone https://github.com/ros-perception/depthimage_to_laserscan.git
cd ..
catkin_make
```
#### 2. Main PC
##### 1. navigation module의 설치
```
sudo apt-get install ros-kinetic(indigo)-navigation
sudo apt-get install ros-kinetic-gmapping
```

##### 2. dynamixel SDK 설치

```
sudo apt-get install ros-kinetic(indigo)-dynamixel-sdk
```

##### 3. Git을 이용한 mybom의 ros navigation package 사용을 위한 설정 파일 설치

```
cd catkin_ws/src
sudo git clone https://github.com/BenedictCheong/Mybom-Kinetic-Navigation.git
cd ..
catkin_make
```

## 3. 실행 방법
채유정 연구원이 제공할 예정.
