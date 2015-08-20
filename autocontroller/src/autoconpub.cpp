/*
 * Course: Arquitectura de computadores (CC4301)
 * University: Universidad de Chile (Chile)
 * Year: 2015
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
using namespace std;

int main(int argc, char **argv){

  // Initiate new ROS node named "autoconpub_node"
  ros::init(argc, argv, "autoconpub_node");
  
  // ROS handler
  ros::NodeHandle n;
  
  // Publisher
  ros::Publisher autocon_pub = n.advertise<std_msgs::String>("autocon", 10);
  ros::Rate loop_rate(1);
  
  bool ready = true;
  
  while (ros::ok()){
    
    cout << "\n";
    cout << "\n I am ready to move!! \n";
    
    // Choose an action! (Acceptable display included)
    
    string a;
    cout << "\n I am ready to move!! \n";
    
    cout << "\n Forward(w), backward(s), right(d)\n";
    cout << "left(a) or end(e)? "; cin >> a;
    
    cout << "\n";
    
    if (a == "w" || a == "s" || a == "d" || a == "a"){
    
      std_msgs::String msg;
      msg.data = a;
      ROS_INFO("%s", msg.data.c_str());
      
      autocon_pub.publish(msg);
      
      ros::spinOnce();
      
      loop_rate.sleep();
      
    } else {
    
      if (a == "e")
        ready = false;
        
      else cout << "Not a defined operation. \n";
    }
  }
  cout << "Goodbye budy! \n";
  return 0;
}
