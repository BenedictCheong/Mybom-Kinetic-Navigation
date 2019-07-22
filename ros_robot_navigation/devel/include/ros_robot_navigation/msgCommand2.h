// Generated by gencpp from file ros_robot_navigation/msgCommand2.msg
// DO NOT EDIT!


#ifndef ROS_ROBOT_NAVIGATION_MESSAGE_MSGCOMMAND2_H
#define ROS_ROBOT_NAVIGATION_MESSAGE_MSGCOMMAND2_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros_robot_navigation
{
template <class ContainerAllocator>
struct msgCommand2_
{
  typedef msgCommand2_<ContainerAllocator> Type;

  msgCommand2_()
    : command_switch(false)  {
    }
  msgCommand2_(const ContainerAllocator& _alloc)
    : command_switch(false)  {
  (void)_alloc;
    }



   typedef uint8_t _command_switch_type;
  _command_switch_type command_switch;




  typedef boost::shared_ptr< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> const> ConstPtr;

}; // struct msgCommand2_

typedef ::ros_robot_navigation::msgCommand2_<std::allocator<void> > msgCommand2;

typedef boost::shared_ptr< ::ros_robot_navigation::msgCommand2 > msgCommand2Ptr;
typedef boost::shared_ptr< ::ros_robot_navigation::msgCommand2 const> msgCommand2ConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_robot_navigation::msgCommand2_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ros_robot_navigation

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'ros_robot_navigation': ['/home/kist/catkin_ws/src/ros_robot_navigation/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4252f9df023e042aa49dab7c037dd8f6";
  }

  static const char* value(const ::ros_robot_navigation::msgCommand2_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4252f9df023e042aULL;
  static const uint64_t static_value2 = 0xa49dab7c037dd8f6ULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_robot_navigation/msgCommand2";
  }

  static const char* value(const ::ros_robot_navigation::msgCommand2_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool command_switch\n\
";
  }

  static const char* value(const ::ros_robot_navigation::msgCommand2_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.command_switch);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct msgCommand2_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_robot_navigation::msgCommand2_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_robot_navigation::msgCommand2_<ContainerAllocator>& v)
  {
    s << indent << "command_switch: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.command_switch);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_ROBOT_NAVIGATION_MESSAGE_MSGCOMMAND2_H
