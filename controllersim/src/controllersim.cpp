
#include "controllersim.h"

#define PI 3.14159265

using namespace std;

/**
 * Creates a "Twist" geometry message with given parameters.
 */
geometry_msgs::Twist movementMessage(double vx, double vy, double vz, double wx, double wy, double wz){

    // --- Create message to be published ---

    // Message to be published
    geometry_msgs::Twist vel_msg;
    
    // Linear velocity
    vel_msg.linear.x = vx;
    vel_msg.linear.y = vy;
    vel_msg.linear.z = vz;
    
    // Angular velocity
    vel_msg.angular.x = wx;
    vel_msg.angular.y = wy;
    vel_msg.angular.z = wz;

    // Retrive created message
    return vel_msg;
}





/**
 * Auxiliary function for straight.
 */
geometry_msgs::Twist straightMovement(double speed, bool isForward){
    if(isForward) return movementMessage(speed,0,0,0,0,0);
    else return movementMessage(-1*speed,0,0,0,0,0);
}

void straightAction(double speed, double distance, bool isForward,
    ros::Publisher vp){
    
    // Prepare for moving loop
    double t0 = ros::Time::now().toSec();
    double traveled_distance = 0.0;
    ros::Rate loop_rate(20);

    while(traveled_distance < distance){
	// Move Robot
	vp.publish(straightMovement(speed,isForward));
            
	// Actualize state
	double t1 = ros::Time::now().toSec();
	traveled_distance = speed * (t1 - t0);
	
	// Listen and wait
	ros::spinOnce();
	loop_rate.sleep();
    }

    // Stop Robot
    vp.publish(straightMovement(0.0, isForward));
}

/**
 * Moves the robot straightly.
 */
void straight(ros::Publisher velocity_publisher){
    
    // Parameters for straightAction function
    double speed, distance; bool isForward;
    cout << "Speed? "; cin >> speed;
    cout << "Distance? "; cin >> distance;
    cout << "Forward? "; cin >> isForward;
    
    straightAction(speed, distance, isForward, velocity_publisher);
} 





/**
 * Auxiliary function for generating rotate movements.
 */
geometry_msgs::Twist rotateMovement(double speed, bool isClockwise){
    if(isClockwise) return movementMessage(0,0,0,0,0,-1*speed);
    else return movementMessage(0,0,0,0,0,speed);
}

/**
 * Auxiliary function for performing rotation.
 */
void rotateAction(double speed, double angle, bool isClockwise, 
    ros::Publisher vp){
    // Prepare for moving loop
    double t0 = ros::Time::now().toSec();
    double traveled_angle = 0.0;
    ros::Rate loop_rate(100);

    while(traveled_angle < angle){
	// Rotate Robot
	vp.publish(rotateMovement(speed,isClockwise));
            
	// Actualize state
	double t1 = ros::Time::now().toSec();
	traveled_angle = speed * (t1 - t0) * (180/PI);
	
	// Listen and wait
	ros::spinOnce();
	loop_rate.sleep();
    }

    // Stop Robot
    vp.publish(rotateMovement(0.0, isClockwise));
}

/**
 * Rotate the robot.
 */
void rotate(ros::Publisher velocity_publisher){
    
    // Parameters for rotateAction function
    double speed, angle; bool isClockwise;
    cout << "Speed? "; cin >> speed;
    cout << "Angle? "; cin >> angle;
    cout << "Clockwise? "; cin >> isClockwise;
    
    rotateAction(speed, angle, isClockwise, velocity_publisher);
    
    return ;
}





void dance(ros::Publisher vp){
    straightAction(5, 3, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 3, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 6, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 6, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 6, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 3, 1, vp);
    rotateAction(3, 89.9, 0, vp);
    straightAction(5, 3, 1, vp);
    rotateAction(3, 89.9, 0, vp);
}



/** 
 * Class for performing movements.
 */
Movement::Movement(ros::Publisher publisher, ros::NodeHandle handle){
	_pub = publisher;
	_sub = handle.subscribe("/turtle1/pose", 1, &Movement::moveCallback, this);
    }

/**
* Routine performed by move function when receiving message.
*/
void Movement::moveCallback(const turtlesim::Pose::ConstPtr& state){

    // Parameters for move function
    double speed, finalXCoor, finalYCoor;
    cout << "Speed? "; cin >> speed;
    cout << "xCoor? "; cin >> finalXCoor;
    cout << "yCoor? "; cin >> finalYCoor;     

    // Getting robot state
    double currentXCoor = state->x,
        xCoor = finalXCoor - currentXCoor; 
    double currentYCoor = state->y,
        yCoor = finalYCoor - currentYCoor;
    double currentAngle = state->theta,    
        finalAngle = atan(xCoor/yCoor),
        angle = finalAngle - currentAngle;

    if(angle>0) rotateAction(speed, angle, 0, _pub);
    else rotateAction(speed, angle, 1, _pub);   

    double distance = sqrt(xCoor*xCoor + yCoor*yCoor);
    straightAction(speed, distance, 1, _pub);       
}



/**
* Moves the robot to a position.
*/
void Movement::move(){

    // Listening loop
    ros::spinOnce();
}
