#include "rosplan_interface/action.h" 
#include <actionlib/client/simple_action_client.h> 
#include <actionlib/client/terminal_state.h> 
#include <assignment_2/PlanningAction.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <unistd.h>

namespace KCL_rosplan {

    ActionInterface::ActionInterface(ros::NodeHandle &nh) {
    // here the initialization
    }
    
    bool ActionInterface::concreteCallback(const      rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
        // here the implementation of the action
        //std::cout << "Going from " << msg->parameters[1].value << " to " << msg->parameters[2].value << std::endl;
        ROS_INFO("Going from (%s) to (%s)", msg->parameters[1].value.c_str(), msg->parameters[2].value.c_str()); 
        //sleep(5);
        //actionlib::SimpleActionClient<assignment_2::PlanningAction> ac("/reaching_goal", true); 
	//assignment_2::PlanningGoal goal;
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true); 
	move_base_msgs::MoveBaseGoal goal;
	ac.waitForServer();
	if(msg->parameters[2].value  == "init"){
	goal.target_pose.header.frame_id  =  "map";
	goal.target_pose.header.stamp  =  ros::Time::now();
	goal.target_pose.pose.position.x  =  0.0;
	goal.target_pose.pose.position.y  =  1.5;
	goal.target_pose.pose.orientation.w  = 1.0;
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
