# Assignment2 Experimental robotics laboratory
## Group Members | Name-Surname & GitHub Account
* Isabel Cebollada Gracia | [@isacg5](https://github.com/isacg5)
* Ecem Isildar | [@ecemisildar](https://github.com/ecemisildar)
* Baris Aker | [@barisakerr](https://github.com/barisakerr)
* Carmine Miceli | [@Carmine00](https://github.com/Carmine00)

## Brief description of the project
The aim of this project is to integrate the ROSPlan package, which uses the PDDL language, to define a plan for a robot with a camera mounted on it to detect four markers autonomously in an environment with obstacles (e.g: walls). The world environment and the robot model are already given. Simulation and real-world tests are done successfully by the group members.

## How to use?
For the execution of this project, is necessary install the necessary dependencies for the planning and autonomous navigation components. For the ROSPlan, with the following command:
```console
sudo apt install flex bison freeglut3-dev libbdd-dev python3-catkin-tools ros-$ROS_DISTRO-tf2-bullet
git clone https://github.com/KCL-Planning/ROSPlan
```
For the mapping component:
```console
sudo apt-get install ros-<ros_distro>-openslam-gmapping
git clone https://github.com/CarmineD8/SLAM_packages
```
For the navigation:
```console
sudo apt-get install ros-<ros_distro>-navigation
sudo apt-get install ros-<ros_distro>-navigation-msgs
```
After completing these needed steps, it is only necessary clone the reposity in the ros workspace, use catkin_make and run the following command:
```console
roslaunch assignment_2 navigation.launch
```

## Brief description of the code
The planning behaviour is carried out by the nodes of the ROSPlan package, a domain __rosbot.pddl__ and a problem file __task.pddl__ are defined in the __/assignment_2/pddl__ folder to achieve the desired goal. <br> It is necessary to integrate the pddl formal actions with nodes that act as a client interface and execute the needed actions by sending the goal to specific action server; the sequence of action is to reach a waypoint, carried out by the node __go_waypoint__, once the waypoint is reached it is necessary to look for the desired marker with __marker_action__ and then at the very end to go back to the inital position with __go_init__. <br>
The mentioned nodes act as clients, therefore an action server of the navigation component __move_base__ was used to reach the single waypoints, whereas for the identification and centering of the marker a dedicated script __find_marker_action.py__ was developed. <br>
Last but not least, the script __services_pddl.py__ calls all the services of the ROSPlan necessary to parse the domain and problem files to generate the plan and then dispatch the action.
The generated plan can be read in __/assignment_2/pddl/plan.pddl__ or with the command __'rostopic echo rosplan_planner_interface/planner_output - p'__.

## Flowchart
To be defined...

## Possible Improvements 
To be defined...

## Videos
To be defined...




