#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int64.h>
#include <geometry_msgs/Point.h>
#include <assignment_2/MarkerDetection.h>

class ArucoMarkerPublisher
{
private:
  // ArUco stuff
  aruco::MarkerDetector mDetector_;
  std::vector<aruco::Marker> markers_;
  aruco::CameraParameters camParam_;

  // node params
  double marker_size_;
  bool useCamInfo_;

  // ROS pub-sub
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;

  ros::Publisher marker_pub_;

  assignment_2::MarkerDetection markers_info;

  cv::Mat inImage_;
  
public:
  ArucoMarkerPublisher() :
      nh_("~"), it_(nh_), useCamInfo_(true)
  {
    // Real robot topic
    // image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ArucoMarkerPublisher::image_callback, this);

    // Old robot /robot/camera1/image_raw
    // Sim robot topic (rosbot)
    image_sub_ = it_.subscribe("/camera/color/image_raw", 1, &ArucoMarkerPublisher::image_callback, this);
    marker_pub_ = nh_.advertise<assignment_2::MarkerDetection>("/marker_pub",1);

    nh_.param<bool>("use_camera_info", useCamInfo_, false);
    camParam_ = aruco::CameraParameters();
  }

  void image_callback(const sensor_msgs::ImageConstPtr& msg)
  {
    markers_info.corners.resize(4);

    ros::Time curr_stamp = msg->header.stamp;
    cv_bridge::CvImagePtr cv_ptr;
    
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      inImage_ = cv_ptr->image;
   
      // clear out previous detection results
      markers_.clear();

      // ok, let's detect
      mDetector_.detect(inImage_, markers_, camParam_, marker_size_, false);

        for (std::size_t i = 0; i < markers_.size(); ++i)
        {

          markers_info.id = markers_.at(i).id;
          markers_info.corners[0].x = markers_.at(i)[0].x;
          markers_info.corners[0].y = markers_.at(i)[0].y;
          markers_info.corners[0].z = 0;

          markers_info.corners[1].x = markers_.at(i)[1].x;
          markers_info.corners[1].y = markers_.at(i)[1].y;
          markers_info.corners[1].z = 0;

          markers_info.corners[2].x = markers_.at(i)[2].x;
          markers_info.corners[2].y = markers_.at(i)[2].y;
          markers_info.corners[2].z = 0;

          markers_info.corners[3].x = markers_.at(i)[3].x;
          markers_info.corners[3].y = markers_.at(i)[3].y;
          markers_info.corners[3].z = 0;

          marker_pub_.publish(markers_info);

          // std::cout << "first" << markers_.at(i)[0] << " second "<< markers_.at(i)[1] << " third "<< markers_.at(i)[2] << " fourth "<< markers_.at(i)[3] <<  " ";
          
        }
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "aruco_marker_publisher");

  ArucoMarkerPublisher node;

  ros::spin();
}
