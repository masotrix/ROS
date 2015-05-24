/*
 * Author: Matias Haeussler
 * Year: 2016
 * Course: Arquitectura de computadores (CC4301)
 * University: Universidad de Chile (Chile)
 *
 */
 
#include "controllersim.h"

using namespace std;



int main(int argc, char **argv)
{
    // Initiate new ROS node named "controllersim_node"
    ros::init(argc, argv, "controllersim_node");
    
    // ROS handler
    ros::NodeHandle n;

    // Publisher
    ros::Publisher velocity_publisher = 
        n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    
    bool ready = true;
    // --- Main loop ---

    while( ros::ok() && ready ) {
	
	cout << "\n";
  	cout << "\n I am ready to move!! \n";      
	
	// Choose an action! (Acceptable display included)

	int i;
	cout << "\n -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- \n";

	cout << "\n Specific dance (1), straight(2), rotate(3)\n";
	cout << "or end(0)? "; cin >> i;
	
	cout << "\n";

	// Actions switch

	switch(i){
	    case 0:
		ready = false;
		break;
	    case 1:
		{
		dance(velocity_publisher);		
		break;
		}
	    case 2:
		straight(velocity_publisher);
		break;
	    case 3:
		rotate(velocity_publisher);
		break;
	    default:
		cout << "Not a defined operation. \n";
    	}
    }
    cout << "Goodbye budy! \n";
    return 0;
}
