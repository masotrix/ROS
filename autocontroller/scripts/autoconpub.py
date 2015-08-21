#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def autoconpub():
 pub = rospy.Publisher('autocontroller', String, queue_size=10)
 rospy.init_node('autoconpub', anonymous=True)
 rate = rospy.Rate(1) # 1 second
 while not rospy.is_shutdown():
 
  print "\n I am ready to move!!"
  
  # Choose an action! (Acceptable display included)
  
  print "\n -+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
  
  print "\n Forward(w), backward(s), right(d),"
  a = raw_input("left(a) or end(ctrl_c)? ")
  print "\n"
  
  if a == "w" or a == "s" or a == "d" or a == "a" :
    pub.publish(a)
    rate.sleep()
    
  else : print "Not a defined operation."
  
if __name__ == '__main__':
  try:
    autoconpub()
  except rospy.ROSInterruptException:
    pass
