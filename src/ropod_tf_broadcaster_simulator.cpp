#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <ros/console.h>
#include <geometry_msgs/PoseArray.h>


nav_msgs::Odometry odommsg;
tf::Quaternion q3;
tf::Transform base2loadTF; // Sending a zero transformation makes configuration easier. It also means there is no load.
ros::Publisher pub_ropod_odom;

// /* 
void poseCallback(const nav_msgs::Odometry::ConstPtr& msg){	
  odommsg.pose.pose.position.x = msg->pose.pose.position.x;
  odommsg.pose.pose.position.y = msg->pose.pose.position.y;
  odommsg.pose.pose.orientation.x = msg->pose.pose.orientation.x;
  odommsg.pose.pose.orientation.y = msg->pose.pose.orientation.y;
  odommsg.pose.pose.orientation.z = msg->pose.pose.orientation.z;
  odommsg.pose.pose.orientation.w = msg->pose.pose.orientation.w;
  odommsg.twist.twist.linear.x = msg->twist.twist.linear.x;
  odommsg.twist.twist.linear.y = msg->twist.twist.linear.y;
  odommsg.twist.twist.linear.z = msg->twist.twist.linear.z;    
  odommsg.twist.twist.angular.x = msg->twist.twist.angular.x;
  odommsg.twist.twist.angular.y = msg->twist.twist.angular.y;
  odommsg.twist.twist.angular.z = msg->twist.twist.angular.z;    
  odommsg.header.frame_id = "/ropod/odom";
  odommsg.child_frame_id = "/ropod/base_link";
  odommsg.header.stamp = ros::Time::now();
  
  q3 = tf::Quaternion(odommsg.pose.pose.orientation.x, odommsg.pose.pose.orientation.y, odommsg.pose.pose.orientation.z, odommsg.pose.pose.orientation.w); 
  
  pub_ropod_odom.publish(odommsg);     
  
}
/* 
*/
/*
void poseCallback(const geometry_msgs::PoseArray::ConstPtr& msg){	
  odommsg.pose.pose.position.x = msg->poses[0].position.x;
  odommsg.pose.pose.position.y = msg->poses[0].position.y;
  odommsg.pose.pose.orientation.x = msg->poses[0].orientation.x;
  odommsg.pose.pose.orientation.y = msg->poses[0].orientation.y;
  odommsg.pose.pose.orientation.z = msg->poses[0].orientation.z;
  odommsg.pose.pose.orientation.w = msg->poses[0].orientation.w;  
  q3 = tf::Quaternion(odommsg.pose.pose.orientation.x, odommsg.pose.pose.orientation.y, odommsg.pose.pose.orientation.z, odommsg.pose.pose.orientation.w); 
  ROS_INFO("Hello %s", "callback");
}
* */
int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;
  
  odommsg.pose.pose.position.x = 0;
  odommsg.pose.pose.position.y = 0;
  odommsg.pose.pose.orientation.x = 0;
  odommsg.pose.pose.orientation.y = 0;
  odommsg.pose.pose.orientation.z = 0;
  odommsg.pose.pose.orientation.w = 0;

  ros::Rate r(30);

  tf::TransformBroadcaster broadcaster;

  
  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  
  tf::Quaternion q2;
  q2.setRPY(0, 0, 3.141592/2);
  
  
  q3.setRPY(0, 0, 0);  
  
   base2loadTF = tf::Transform(q, tf::Vector3(0.0, 0.0, 0.0));
  
   pub_ropod_odom = n.advertise<nav_msgs::Odometry>("/ropod/odom", 1);
   ros::Subscriber sub = n.subscribe<nav_msgs::Odometry>("/ropod/odom_incomplete", 1, poseCallback);
  //ros::Subscriber sub = n.subscribe<geometry_msgs::PoseArray>("/ed/localization/particles", 1, poseCallback);
  
  while(n.ok()){
	  // q2 = (tf::Quaternion) odommsg.pose.pose.orientation;
    /* broadcaster.sendTransform(
     tf::StampedTransform(
        tf::Transform(q, tf::Vector3(0.25, 0.0, 0.15)),
        ros::Time::now(),"/ropod/base_link", "/ropod/laser/scan"));*/ // This transformation is configured using static_tf.launch in ropod_bringup/parameters folder
        
    
    
    /* Sending a zero transformation makes configuration easier. It also means there is no load */    
   broadcaster.sendTransform(
      tf::StampedTransform(base2loadTF, ros::Time::now(),"/ropod/base_link", "/load/base_link"));
    
	broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(q3, tf::Vector3(odommsg.pose.pose.position.x, odommsg.pose.pose.position.y, 0.0)),        
        //tf::Transform(q, tf::Vector3(0.0, 0.0, 0.3)),
        ros::Time::now(),"/ropod/odom","/ropod/base_link"));      
    
     
    ros::spinOnce();           
    r.sleep();
  }
}
