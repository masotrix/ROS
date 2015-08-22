#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import rospy
form std_msgs.msg import String

# GPIO setup
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)

servo1 = GPIO.PWM(11, 50)
servo2 = GPIO.PWM(13, 50)

s1fs = 30
s2fs = 30
s1bs = 70
s2bs = 70

def callback(data):
 a =data.data
 if a == "w":
   print "Moving forward"
   servo1.start(s1fs)
   servo2.start(s2fs)
 elif a == "s":
   print "Moving backward"
   servo1.start(s1bs)
   servo2.start(s2bs)
 elif a == "d":
   print "Moving to the right"
   servo1.start(s1fs)
 else :
   print "Moving to the left"
   servo2.start(s2fs)
 time.sleep(1)
 servo1.stop()
 servo2.stop()
 
 
def listener():
 rospy.init_node('autoconsub', anonymous=True)
 print "Ready to hear!"
 rospy.Subscriber('autocontroller', String, callback)
 rospy.spin()
 
if __name__ == '__main__':
 listener()
 GPIO.cleanup()
