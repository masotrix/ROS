Package: autocontroller
Description:
  Control two servos for an auto-robot (wheels). It can move them both forward, backwards, or two-way mixed (left and right).
Usage: 
  -Download package, put it into your src catkin workspace folder, and make both autoconpub.py and autoconsub.py executable 
   (with chmod +x autoconpub.py and chmod +x autoconsub.py).
  -Then, use in different terminals: 
    1) roscore 
    2) rosrun autocontroller autoconpub.py
    3) rosrun autocontroller autoconsub.py
  -Finally, command the robot through autoconpub.py terminal.
Comments:
  Other files (like cpp ones) are being added for a c++ version of the controller.
