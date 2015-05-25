
#include controllersim.h

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
