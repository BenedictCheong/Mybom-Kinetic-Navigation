NavigationSetupforMybom
===========================================================
Git global setup
git config --global user.name "Howon Cheong"
git config --global user.email "howoncheong@gmail.com"

Create a new repository
git clone git@gitlab.com:howoncheong/ros_robot_navigation.git
cd ros_robot_navigation
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master

Push an existing folder
cd existing_folder
git init
git remote add origin git@gitlab.com:howoncheong/ros_robot_navigation.git
git add .
git commit -m "Initial commit"
git push -u origin master

Push an existing Git repository
cd existing_repo
git remote rename origin old-origin
git remote add origin git@gitlab.com:howoncheong/ros_robot_navigation.git
git push -u origin --all
git push -u origin --tags




## 1. Description

NavigationSetupforMybom: Mybom의 Realsense R200 camera 를 이용한 자율 주행 Module 의 설치 및 setup
- PerceptionIntercontroller : Perception data management와 Arbi Framework의 Interface
- TaskIntercontroller : ActionExecution와의 Arbi Framework의 Interface

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
sudo apt-get install ros-indigo-navigation (indigo)
sudo apt-get install ros-kinetic-navigation (kinetic)
```
cd catkin_ws/src/
catkin_create_pkg robot_setup_tf roscpp tf geometry_msgs

```
cd existing_folder
git init
git remote add origin git@gitlab.com:howoncheong/robot_setup_tf.git
git add .
git commit -m "Initial commit"
git push -u origin master

#### 2. 

#### 1. rosjava install (rosjava가 설치되어 있는지 확인 후, 설치가 안되어 있을 시에만 설치)

이 모듈의 의존 Python package는 아래의 명령어를 통해 설치 가능하다.

```
sudo apt-get install ros-kinetic-catkin ros-kinetic-rospack python-wstool openjdk-8-jdk

mkdir -p ~/rosjava/src
wstool init -j4 ~/rosjava/src https://raw.githubusercontent.com/rosjava/rosjava/kinetic/rosjava.rosinstall
source /opt/ros/kinetic/setup.bash
cd ~/rosjava
rosdep update
rosdep install --from-paths src -i -y
catkin_make

cd rosjava/rosjava_core
./gradlew Install
./gradlew docs
./gradlew test
./gradlew eclipse

```

#### 2. InterfaceManagerDementia 프로젝트 import
- InterfaceManagerDementia 프로젝트 eclipse-workspace로 복사
- eclipse 실행
- file -> import -> General -> Existing Porjects into Workspace -> InterfaceManagerDementia 선택

#### 3. rosjava Project import
-  file -> import -> General -> Projects from Folder or Archive -> ~/rosjava/rosjava_core/rosjava 선택


#### 3. Dependency Library 설정
- Project Explorer Tab에서 InterfaceManagerDementia 프로젝트 선택 후, 오른쪽 버튼 클릭 후 Properties for Behavior 클릭
- Jav Build Path Tab 선택 후, Projects Tab에서 Add 선택, rosjava 클릭
- Java Build Path 선택 후, Libraries Tab 선택 후, Add ExternalJars 클릭
- ~/catkin_ws/devel/share/maven/org/ros/rosjava_bootstrap/message_generation/0.3.3/message_generation-0.3.3.jar 선택
- /home/kist/.gradle/caches/modules-2/files-2.1/org.apache.commons/com.springsource.org.apache.commons.logging/1.1.1/7657caf2c78e1d79c74d36f2ae128a115f7cc180/com.springsource.org.apache.commons.logging-1.1.1.jar 선택



## 3. Usage
--------

### 1. roscore 실행
```
roscore
```
### 2. IP ADDRESS 확인
```
ifconfig
```
- eth0 -> inet addr가 IP_ADDRESS

### 3. Arbi launch 실행
```
- ArbiFramework-0.8 > src > kr.ac.uos.ai.arbi > Launcher.java에서 JMS_BROKER_URL 셋팅 후, 싫행
  <JSM_BROKER_URL = IP_ADDRESS>

### 4. Perception PC의 Perception_data_management 실행
```
rosrun perception_data_mangaement perception_data_management
```
### 5. Main Pc의 Action Exeuction 실행
```
(Action Exeuction 실행 명령어)
```
### 6. InterfaceManagerDementia 실행
-   <JSM_BROKER_URL = IP_ADDRESS> 셋팅
- PerceptionIntercontroller.java 실행
- TaskIntercontroller.java 실행
