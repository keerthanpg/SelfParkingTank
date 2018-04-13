import serial 
import syslog
import time
import argparse
import numpy as np


#The following line is for serial over GPIO
port = '/dev/ttyACM0' # note I'm using Mac OS-X

ard = serial.Serial(port,10,timeout=10)
time.sleep(2) # wait for Arduino

val1=0



while (1):
# Serial write section
    #ard.flush() 
    # Serial read section
    msg = ard.read(ard.inWaiting()) # read all characters in buffer    
    #msg=msg.decode("utf-8") 
    print (msg)
        
    