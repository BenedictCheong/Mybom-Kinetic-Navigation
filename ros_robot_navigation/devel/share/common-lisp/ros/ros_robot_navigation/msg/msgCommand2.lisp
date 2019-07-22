; Auto-generated. Do not edit!


(cl:in-package ros_robot_navigation-msg)


;//! \htmlinclude msgCommand2.msg.html

(cl:defclass <msgCommand2> (roslisp-msg-protocol:ros-message)
  ((command_switch
    :reader command_switch
    :initarg :command_switch
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass msgCommand2 (<msgCommand2>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msgCommand2>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msgCommand2)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_robot_navigation-msg:<msgCommand2> is deprecated: use ros_robot_navigation-msg:msgCommand2 instead.")))

(cl:ensure-generic-function 'command_switch-val :lambda-list '(m))
(cl:defmethod command_switch-val ((m <msgCommand2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_robot_navigation-msg:command_switch-val is deprecated.  Use ros_robot_navigation-msg:command_switch instead.")
  (command_switch m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msgCommand2>) ostream)
  "Serializes a message object of type '<msgCommand2>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'command_switch) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msgCommand2>) istream)
  "Deserializes a message object of type '<msgCommand2>"
    (cl:setf (cl:slot-value msg 'command_switch) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msgCommand2>)))
  "Returns string type for a message object of type '<msgCommand2>"
  "ros_robot_navigation/msgCommand2")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msgCommand2)))
  "Returns string type for a message object of type 'msgCommand2"
  "ros_robot_navigation/msgCommand2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msgCommand2>)))
  "Returns md5sum for a message object of type '<msgCommand2>"
  "4252f9df023e042aa49dab7c037dd8f6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msgCommand2)))
  "Returns md5sum for a message object of type 'msgCommand2"
  "4252f9df023e042aa49dab7c037dd8f6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msgCommand2>)))
  "Returns full string definition for message of type '<msgCommand2>"
  (cl:format cl:nil "bool command_switch~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msgCommand2)))
  "Returns full string definition for message of type 'msgCommand2"
  (cl:format cl:nil "bool command_switch~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msgCommand2>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msgCommand2>))
  "Converts a ROS message object to a list"
  (cl:list 'msgCommand2
    (cl:cons ':command_switch (command_switch msg))
))
