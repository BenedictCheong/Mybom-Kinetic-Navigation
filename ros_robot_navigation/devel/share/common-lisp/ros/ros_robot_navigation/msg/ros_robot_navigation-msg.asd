
(cl:in-package :asdf)

(defsystem "ros_robot_navigation-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "msgCommand2" :depends-on ("_package_msgCommand2"))
    (:file "_package_msgCommand2" :depends-on ("_package"))
  ))