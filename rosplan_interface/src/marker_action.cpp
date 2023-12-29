#include "rosplan_interface/action.h" 
#include <actionlib/client/simple_action_client.h> 
#include <actionlib/client/terminal_state.h> 
#include <assignment_2/MarkerAction.h>
#include <unistd.h>

namespace KCL_rosplan {

    ActionInterface::ActionInterface(ros::NodeHandle &nh) {
    // here the initialization
    }
    
    bool ActionInterface::concreteCallback(const      rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
        ROS_INFO("Looking marker (%s)", msg->parameters[1].value.c_str()); 
        //sleep(5);
        actionlib::SimpleActionClient<assignment_2::MarkerAction> ac("/reaching_goal_marker", true); 
	assignment_2::MarkerGoal goal;
	ac.waitForServer();
	if(msg->parameters[1].value  == "m11"){ 
	goal.target_marker  =  11;
	}
	else if (msg->parameters[1].value  == "m12"){
	goal.target_marker  =  12;
	}
	else if (msg->parameters[1].value  == "m13"){
	goal.target_marker  =  13;
	}
	else if (msg->parameters[1].value  == "m15"){
	goal.target_marker  =  15;
	}
	ac.sendGoal(goal); 
	ac.waitForResult();
        ROS_INFO("Action (%s) performed: completed!", msg->name.c_str()); 
        return true;
    }
}
int main(int argc, char **argv) {
    ros::init(argc, argv, "my_rosplan_action",     ros::init_options::AnonymousName); 
    ros::NodeHandle nh("~"); 
    KCL_rosplan::ActionInterface my_aci(nh);
    my_aci.runActionInterface(); 
    return 0;
}
