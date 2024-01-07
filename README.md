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
![Flowchart is given below:](https://github.com/Carmine00/assignment2_EXP_rep/blob/main/resources/assignment2.png)

## Possible improvements 
* The default global planner used by the MoveBase package is Dijkstra’s algorithm but other choices such as A* or Carrot Planner could have been investigated, so as to study how the response time to complete the task changes based on the underlying implementation and choose based on this analysis the best option; the same reasoning holds for the local planner which was dwa but other options like eband and teb were available.
* The algorithm used for mapping was based on Gmapping, which is a filtering based-approach, but another possible solution to be tested could have been an optimization-based approach such as KartoSlam.
* The PDDL planning part was carried out assuming a solution to the given problem exists, moreover actions were assumed to be always successful. If these assumptions were dropped a more complex and general behaviour would be required to be investigated; some possible solutions in case the generation of the plan fails could be to require in input a new problem or try to solve a smaller part of the problem, whereas concerning the failure of a single action it could be possible to implement a recovery behaviour such as replan again or to reach the initial point and wait for further commands from the user.

## Videos
<p align="justify">
  Watch the video using the simulated robot robot here
</p>

[![Watch the video](https://github.com/Carmine00/assignment2_EXP_rep/blob/main/resources/img.png)](https://youtu.be/EKx9IrjO614)




