#! /usr/bin/env python3

import rospy
from geometry_msgs.msg import Point, Pose, Twist
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import Odometry
from std_msgs.msg import Int64
import math
import actionlib
import actionlib.msg
from tf import transformations
from std_srvs.srv import *
import time
import assignment_2.msg
from assignment_2.msg import MarkerDetection

IMG_WIDTH = 640 # previous 800
IMG_HEIGHT = 480 # previous 800
EXTRA_RANGE = 40
LIMIT_DISTANCE = 200

# Velocity for real robot: 0.1

class RobotController():
    def __init__(self):
        self.state = 0
        self.center_point = Point()
        self.target_marker = 0
        self.current_marker = 0
        self.marker_width = 0
        self.vel_msg = Twist()
        self.pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
        self.sub = rospy.Subscriber('/marker_pub', MarkerDetection, self.cb_marker)

        self.act_s = actionlib.SimpleActionServer(
        '/reaching_goal_marker', assignment_2.msg.MarkerAction, self.find_marker, auto_start=False)
        self.act_s.start()


    def find_marker(self, goal):
        rospy.loginfo("Goal received..")

        self.target_marker = goal.target_marker
        rospy.loginfo("Looking for marker %d", self.target_marker)

        rate = rospy.Rate(20)
        success = True

        feedback = assignment_2.msg.MarkerFeedback()
        result = assignment_2.msg.MarkerResult()

        
        while not rospy.is_shutdown():
            self.vel_msg.linear.x = 0
            self.vel_msg.linear.y = 0
            self.vel_msg.linear.z = 0
            self.vel_msg.angular.x = 0
            self.vel_msg.angular.y = 0
            self.vel_msg.angular.z = 0

            if self.act_s.is_preempt_requested():
                rospy.loginfo('Goal was preempted')
                self.act_s.set_preempted()
                success = False
                break

            elif self.state == 0:
                rospy.loginfo("ROTATING... ")
                feedback.stat = "Looking for marker"
                self.act_s.publish_feedback(feedback)
                self.rotation_state()

            elif self.state == 1:
                rospy.loginfo("CENTERING...")
                feedback.stat = "Centering marker"
                self.act_s.publish_feedback(feedback)
                self.centering_state()

            elif self.state == 2:
                time.sleep(4)
                rospy.loginfo("Marker detected!")
                feedback.stat = "Marker detected!"
                self.act_s.publish_feedback(feedback)
                break

            else:
                rospy.logerr('Unknown state!')

            self.pub.publish(self.vel_msg)

            rate.sleep()


        if success:
            rospy.loginfo('Goal: Succeeded!')
            self.state = 0
            self.act_s.set_succeeded(result)


    # Callback of the subscription to the topic to get the custom message with information from the marker
    def cb_marker(self, msg):
        self.current_marker = msg.id
        self.center_point.x = ((msg.corners[0].x - msg.corners[1].x)/2)+msg.corners[1].x
        self.center_point.y = ((msg.corners[1].y - msg.corners[2].y)/2)+msg.corners[2].y
        self.marker_width = msg.corners[0].x - msg.corners[1].x


    # Rotation state function that keeps rotating with a constant velocity
    def rotation_state(self):
        print("Current goal:", self.target_marker, " marker currently seeing:", self.current_marker)

        if(self.current_marker == self.target_marker):
            print("Found!")
            self.state = 1
            self.vel_msg.angular.z = 0

        else:
            self.vel_msg.angular.z = 1.0


    # State to center the marker in the middle once seen in the camera, the velocities are changing depending to the distance
    def centering_state(self):
        if(self.center_point.x < (IMG_WIDTH/2-EXTRA_RANGE)):
            # Rotate to the left
            vel = -0.004*self.center_point.x+2.2
            self.vel_msg.angular.z = 0.2

        elif(self.center_point.x > (IMG_WIDTH/2+EXTRA_RANGE)):
            # Rotate to the right
            vel = -0.00334*self.center_point.x-0.5
            self.vel_msg.angular.z = -0.2

        elif(self.center_point.x > (IMG_WIDTH/2-EXTRA_RANGE) and self.center_point.x < (IMG_WIDTH/2+EXTRA_RANGE)):
            print("Centered!")
            self.state = 2
            self.vel_msg.angular.z = 0


    
if __name__ == "__main__":
    time.sleep(2)

    rospy.init_node('find_marker')

    robot_controller = RobotController()
 
    rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        rate.sleep()
