#ifndef CONTROLLERSIM_H
#define CONTROLLERSIM_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <math.h>

void straight(ros::Publisher velocity_publisher);
void rotate(ros::Publisher velocity_publisher);
void dance(ros::Publisher velocity_publisher);
class Movement{
    private:
        ros::Publisher _pub;
        ros::Subscriber _sub;
    
    public:
        Movement(ros::Publisher publisher,ros::NodeHandle handle);
	void moveCallback(const turtlesim::Pose::ConstPtr& state);
 	void move();
};

#endif
