#! /usr/bin/env python3

import rospy
from tf import transformations
from std_srvs.srv import *
from rosplan_dispatch_msgs.srv import DispatchService, DispatchServiceRequest
import time



class ServicesPddl():
    def __init__(self):
        self.service_list = [
            "/rosplan_problem_interface/problem_generation_server",
            "/rosplan_planner_interface/planning_server",
            "/rosplan_parsing_interface/parse_plan",
            "/rosplan_plan_dispatcher/dispatch_plan"
        ]
        self.service_num = 4

    def call(self):
        for i in range(self.service_num):
            rospy.wait_for_service(self.service_list[i])
            try:
                if i == self.service_num - 1:
                    req_dispatcher = DispatchServiceRequest()
                    dispatch_serv = rospy.ServiceProxy(self.service_list[i], DispatchService)
                    dispatch_serv(req_dispatcher)
                else:
                    empty_serv = rospy.ServiceProxy(self.service_list[i], Empty)
                    empty_serv()
            except rospy.ServiceException as e:
                rospy.loginfo("Service call failed: %s" % e)

        

    
if __name__ == "__main__":
    time.sleep(2)

    rospy.init_node('call_services_pddl')

    robot_service = ServicesPddl()
    robot_service.call()
 
    rospy.spin()
