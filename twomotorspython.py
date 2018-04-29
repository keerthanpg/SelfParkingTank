import serial 
import syslog
import time
import serial
import argparse
#import numpy as np

import signal 

#The following line is for serial over GPIO
port = '/dev/ttyACM0' # note I'm using Mac OS-X
ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) # wait for Arduino
f=open('calibration', 'a')
cond = 0	# Default value is 0


#class GracefulKiller:
#  kill_now = False
#  def __init__(self):
#    signal.signal(signal.SIGINT, self.exit_gracefully)
#    signal.signal(signal.SIGTERM, self.exit_gracefully)#

#  def exit_gracefully(self,signum, frame):
#    self.kill_now = True

def sendtoard():
    for i in range(2):
        time.sleep(2)
        
	# Every single digit to each motor should be 3 digits long
	# therefore  Keerthana has initialised the 0 as 100, which
	# explains why -355 in arduino code
        for j in range(479, 712, 1):
            ard.flush()            
            val1 = str( format(int(j), '03d') )
            val2 = str( format(int(j), '03d') )
	
            ard.write((val1+val2).encode('utf-8'))        
            time.sleep(1) # I shortened this to match the new value in your Arduino code
            
	    # Serial read section
            msg = ard.read(ard.inWaiting()) # read all characters in buffer        
            msg=msg.decode("utf-8") 
            if not msg.isspace():
                print(j)
                print (msg)
                f.write('\n')
                f.write(msg)
		print (msg)
            time.sleep(0.2)

        #    if killer.kill_now:
	#	cond = 1
		#print ('Yo mama')
      	#	break
	#if (cond == 1):
	#	break
    	#    if (0xFF == ord('q')):
       	#    	cond = 1	# Condition 1 means break all for loops ...
	#    	break
	#if (cond == 1):
	#	break


if __name__ == "__main__":
	
	
	sendtoard()
	f.close()

